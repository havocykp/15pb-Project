// ProcessList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <windows.h>
#include "SecurityGuard.h"
#include "ProcessList.h"


// CProcessList

IMPLEMENT_DYNAMIC(CProcessList, CListCtrl)

CProcessList::CProcessList()
{

}

CProcessList::~CProcessList()
{
}


BEGIN_MESSAGE_MAP(CProcessList, CListCtrl)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CProcessList::OnNMRClick)
	ON_COMMAND(ID_SHOWTHREAD, &CProcessList::OnShowThread)
	ON_COMMAND(ID_SHOW_MODULE, &CProcessList::OnShowModule)
	ON_COMMAND(ID_SHOW_HEAP, &CProcessList::OnShowHeap)
	ON_COMMAND(ID_TERMINATE_PROCESS, &CProcessList::OnTerminateProcess)
	ON_COMMAND(ID_Hook, &CProcessList::OnHook)
END_MESSAGE_MAP()

void CProcessList::InsertColumnCustom(DWORD dwCount, ...)
{
	//������չ��ʽ
	SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//��ȡ�ߴ�
	CRect rc;
	GetClientRect(&rc);
	INT nTotalWidth = (INT)rc.Width();
	INT nUsedWidth = 0;
	INT nWidth; //ÿ��column�Ŀ��
	va_list list;
	va_start(list, dwCount);
	for (DWORD i = 0; i < dwCount; i++) {
		DOUBLE  fWidthRate = va_arg(list, DOUBLE);
		if (i != dwCount - 1) {
			nWidth = (INT)(nTotalWidth * fWidthRate);
		}
		else {
			nWidth = nTotalWidth - nUsedWidth; //����п�ʹ��ʣ������п��
		}

		if (nWidth < 10) {
			MessageBox(L"Warning: �б�Ŀ��̫С��\n");
		}

		WCHAR* wStr = va_arg(list, WCHAR*);

		InsertColumn(i, wStr, 0, nWidth);
		nUsedWidth += nWidth;
	}
	va_end(list);

	return;
}


void CProcessList::InsertItemCustom(DWORD dwCount, ...)
{
	va_list list;
	va_start(list, dwCount);
	//����λ�ò���һ��
	InsertItem(0, L"");
	for (DWORD i = 0; i < dwCount; i++) {
		WCHAR* wStr = va_arg(list, WCHAR*);
		SetItemText(0, i, wStr);
	}

	va_end(list);
	return;
}


// CProcessList ��Ϣ�������
void CProcessList::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)
	{
		DWORD dwPos = GetMessagePos();
		CPoint point(LOWORD(dwPos), HIWORD(dwPos));
		CMenu menu;
		//����̲߳���  
		VERIFY(menu.LoadMenu(IDR_MENU1));           //������������1�ж����MENU���ļ�����  
		CMenu* popup = menu.GetSubMenu(0);
		ASSERT(popup != NULL);
		popup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

		//��������д�����Ҫ��Ϊ�˺���Ĳ���Ϊ׼����  
		//��ȡ�б���ͼ�ؼ��е�һ����ѡ�����λ��    
		POSITION m_pstion = GetFirstSelectedItemPosition();
		//�ú�����ȡ��posָ�����б����������Ȼ��pos����Ϊ��һ��λ�õ�POSITIONֵ  
		INT m_nIndex = GetNextSelectedItem(m_pstion);

		//��ȡPID
		int nColumn = 0; //pid���ڵ���
		CString strPID = GetItemText(m_nIndex, nColumn);
		//MessageBox(strPID);
		m_nChoosedPid = _wtoi(strPID);
	}
}


void CProcessList::OnShowThread()
{
	// TODO: �ڴ���������������
	m_pThreadDialog = new CThreadDlg();

	m_pThreadDialog->m_pid = m_nChoosedPid;
	m_pThreadDialog->DoModal();
}


void CProcessList::OnShowModule()
{
	// TODO: �ڴ���������������
	m_pModuleDialog = new CModuleDlg();

	m_pModuleDialog->m_pid = m_nChoosedPid;
	//m_pModuleDialog->DoModal();
	m_pModuleDialog->Create(IDD_DIALOG_MODULE, this);
	//m_pModuleDialog->SendMessage(WM_PID_CHOOSED, 0, 255); //test
	m_pModuleDialog->ShowWindow(SW_SHOW);
}



void CProcessList::OnShowHeap()
{
	// TODO: �ڴ���������������
	m_pHeapDialog = new CHeapDlg();
	m_pHeapDialog->m_pid = m_nChoosedPid;
	m_pHeapDialog->DoModal();
}


void CProcessList::OnTerminateProcess()
{
	// TODO: �ڴ���������������
	HANDLE  hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, m_nChoosedPid);
	if (hProcess == INVALID_HANDLE_VALUE) {
		MessageBox(L"�޷���ȡ���̾��");
		return;
	}
	if (!TerminateProcess(hProcess, 0)) {
		MessageBox(L"��ֹ����ʧ��");
	}
}

HANDLE GetThePidOfTargetProcess(HWND hwnd)
{
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE hProcess = ::OpenProcess(PROCESS_ALL_ACCESS | PROCESS_CREATE_THREAD, 0, pid);
	return hProcess;
}

// ����Ȩ��
void Up()
{
	HANDLE hToken;
	LUID luid;
	TOKEN_PRIVILEGES tp;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid);
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	tp.Privileges[0].Luid = luid;
	AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_ADJUST_PRIVILEGES), NULL, NULL);

}

// ����ע��
BOOL DoInject(char* DllPath, HANDLE hProcess)
{
	DWORD BufSize = strlen(DllPath) + 1;
	LPVOID AllocAddr = VirtualAllocEx(hProcess, NULL, BufSize, MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(hProcess, AllocAddr, DllPath, BufSize, NULL);
	PTHREAD_START_ROUTINE pfnStartAddr = (PTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryA");
	HANDLE hRemoteThread;
	hRemoteThread = CreateRemoteThread(hProcess, NULL, 0, pfnStartAddr, AllocAddr, 0, NULL);
	if (hRemoteThread)
	{
		MessageBox(NULL, TEXT("ע��ɹ�"), TEXT("��ʾ"), MB_OK);
		return true;
	}
	else
	{
		MessageBox(NULL, TEXT("ע��ʧ��"), TEXT("��ʾ"), MB_OK);
		return false;
	}
}

void CProcessList::OnHook()
{
	// TODO: �ڴ���������������
	HWND hwnd = FindWindowExA(NULL, NULL, NULL, "��ȫ��ʿ");
	Up();
	HANDLE hP = GetThePidOfTargetProcess(hwnd);
	// ��ʼע��
	// Dll·��
	DoInject("C:\\Users\\yakun\\Desktop\\dllmain\\dllmain.dll", hP);
}
