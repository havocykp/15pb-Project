// PageProc.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TaskManager.h"
#include "PageProc.h"
#include "afxdialogex.h"
#include <Tlhelp32.h>
#include <Psapi.h>

#pragma comment(lib, "Psapi.lib")
// CPageProc �Ի���

IMPLEMENT_DYNAMIC(CPageProc, CDialogEx)

CPageProc::CPageProc(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE_PROCESS, pParent)
{

}

CPageProc::~CPageProc()
{
}

void CPageProc::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROC, m_Proc);
}


BEGIN_MESSAGE_MAP(CPageProc, CDialogEx)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PROC, &CPageProc::OnNMRClickListProc)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_PROC, &CPageProc::OnLvnColumnclickListProc)
END_MESSAGE_MAP()


// CPageProc ��Ϣ�������

// ������ش���
DWORD CPageProc::m_SortColum = 0;
BOOL CPageProc::m_bAs = TRUE;

int CALLBACK CPageProc::MyListCompar(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	// ͨ�����ݵĲ������õ�CSortList����ָ�룬�Ӷ��õ�����ʽ
	CListCtrl* pListCtrl = (CListCtrl*)lParamSort;

	// ͨ��ItemData��ȷ������
	int iCompRes;
	CString szComp1 = pListCtrl->GetItemText(lParam1, m_SortColum);
	CString szComp2 = pListCtrl->GetItemText(lParam2, m_SortColum);

	switch (m_SortColum)
	{
	case (2): case(3): case (4):
		// �Ե�һ��Ϊ��������  ���
		// _ttol
		// atof
		iCompRes = _ttol(szComp1) <= _ttol(szComp2) ? -1 : 1; // ���������Ƚ�
		break;

	default:
		iCompRes = szComp1.Compare(szComp2); // �ַ����Ƚ�
		break;
	}

	// ���ݵ�ǰ������ʽ���е���
	if (m_bAs)
		return iCompRes;
	else
		return -iCompRes;
}

// ��ȡCPUʹ����
double FILETIME2Double(const _FILETIME& fileTime)
{
	return double(fileTime.dwHighDateTime*4.294967296e9) +
		double(fileTime.dwLowDateTime);
}

int GetCpuUsage()
{
	_FILETIME idleTime, kernelTime, userTime;
	GetSystemTimes(&idleTime, &kernelTime, &userTime);
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	WaitForSingleObject(hEvent, 1000);
	_FILETIME newIdleTime, newKernelTime, newUserTime;
	GetSystemTimes(&newIdleTime, &newKernelTime, &newUserTime);
	double dOldIdleTime = FILETIME2Double(idleTime);
	double dNewIdleTime = FILETIME2Double(newIdleTime);
	double dOldKernelTime = FILETIME2Double(kernelTime);
	double dNewKernelTime = FILETIME2Double(newKernelTime);
	double dOldUserTime = FILETIME2Double(userTime);
	double dNewUserTime = FILETIME2Double(newUserTime);

	return int(100.0 - (dNewIdleTime - dOldIdleTime) /
		(dNewKernelTime - dOldKernelTime + dNewUserTime - dOldUserTime) * 100.0);
}


BOOL CPageProc::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	HANDLE hProcess = NULL;
	// ���ñ�ǩ
	m_Proc.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_Proc.InsertColumn(0, _T("ӳ������"), LVCFMT_LEFT, 100);
	m_Proc.InsertColumn(1, _T("PID"), LVCFMT_LEFT, 70);
	m_Proc.InsertColumn(2, _T("CPU"), LVCFMT_LEFT, 60);
	m_Proc.InsertColumn(3, _T("�ڴ�"), LVCFMT_LEFT, 50);
	m_Proc.InsertColumn(4, _T("·��"), LVCFMT_LEFT, 400);

	// ��ȡ������Ϣ
	PROCESSENTRY32 pe = { sizeof(PROCESSENTRY32) };
	//1 ��������
	HANDLE hSnap = CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS, //��Ҫ�����Ŀ�������
		0                   //�����ID��������ģ����ջ��߶ѿ��յ�ʱ������
	);

	//2 �õ���һ��������Ϣ
	BOOL bSuccess = Process32First(hSnap, &pe);
	
	int iLine = m_Proc.GetItemCount();
	//3 ѭ���������еĽ�����Ϣ
	if (bSuccess == TRUE)
	{
		do
		{	
			CString id;
			id.Format(L"%d", pe.th32ProcessID); // ��ȡPID
			m_Proc.InsertItem(iLine, pe.szExeFile, NULL); // ��������
			m_Proc.SetItemText(iLine, 1, id);

			// ��ȡ·��
			CString strPath;
			hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe.th32ProcessID);
			
			GetModuleFileNameEx(hProcess, NULL, strPath.GetBufferSetLength(MAX_PATH), MAX_PATH);
			m_Proc.SetItemText(iLine, 4, strPath);

			// ��ȡ�ڴ���Ϣ
			CString Info;
// 			MEMORYSTATUS mem;
// 			GlobalMemoryStatus(&mem);
// 			Info.Format(L"%d", mem.dwMemoryLoad);
/*			m_Proc.SetItemText(iLine, 3, Info);*/
			hProcess = GetCurrentProcess();
			PROCESS_MEMORY_COUNTERS pmc;
			GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc));
			Info.Format(L"%d", (pmc.WorkingSetSize / 1000));
			m_Proc.SetItemText(iLine, 3, Info);

			// ��ȡcpuռ����
			CString cpu;
			cpu.Format(L"%d%%", GetCpuUsage());
			m_Proc.SetItemText(iLine, 2, cpu);
			
		} while (Process32Next(hSnap, &pe));
	}
	


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CPageProc::OnNMRClickListProc(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int istat = m_Proc.GetSelectionMark();
	m_strSelectedTopic = m_Proc.GetItemText(istat, 1);

	POINT point;
	HMENU hMenu, hSubMenu;
	GetCursorPos(&point);
	hMenu = LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENU_TOPICR));
	hSubMenu = GetSubMenu(hMenu, 0);

	SetMenuDefaultItem(hSubMenu, -1, FALSE);
	SetForegroundWindow();

	TrackPopupMenu(hSubMenu, 0, point.x, point.y, 0, m_Proc, NULL);
	*pResult = 0;
}


void CPageProc::OnLvnColumnclickListProc(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ������ش���
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	m_SortColum = pNMListView->iSubItem;
	m_bAs != m_bAs; // �����ǽ���

	int count = m_Proc.GetItemCount(); // ����
	for (int i = 0; i < count; ++i) {
		m_Proc.SetItemData(i, i);
	}
	m_Proc.SortItems(MyListCompar, (LPARAM)&m_Proc);
	*pResult = 0;
}


