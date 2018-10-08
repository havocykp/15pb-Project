// DlgOne2One.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chatclient.h"
#include "DlgOne2One.h"
#include "afxdialogex.h"

// CDlgOne2One �Ի���

IMPLEMENT_DYNAMIC(CDlgOne2One, CDialogEx)

CDlgOne2One::CDlgOne2One(/*SOCKET sClient ,*/CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgOne2One::IDD, pParent)
	, m_strShow(_T(""))
	, m_strSend(_T(""))
// 	, m_FilePath(_T(""))
// 	, m_sClient(sClient)
{

}

CDlgOne2One::~CDlgOne2One()
{
}

void CDlgOne2One::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LIAOTIAN, m_strShow);
	DDX_Text(pDX, IDC_EDIT2_SEND, m_strSend);
}


BEGIN_MESSAGE_MAP(CDlgOne2One, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ProcSend, &CDlgOne2One::OnBtnProcSend)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_SENDFILE, &CDlgOne2One::OnBnClickedButtonSendfile)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CDlgOne2One ��Ϣ�������


void CDlgOne2One::OnBtnProcSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_strSend.IsEmpty())
	{
		return;
	}

	CString strOne2One;
	GetWindowText(strOne2One);
	strOne2One += L":" + m_strSend;
	CStringA str = CW2A(strOne2One.GetBuffer(), CP_THREAD_ACP);
	CDlgChatMain* pParent = (CDlgChatMain*)GetParent();
	pParent->m_pClient->Send(ONE2ONE, str.GetBuffer(), str.GetLength() + 1);
	// ��ʾ���Լ��ĶԻ�����
	m_strShow += "��˵��";
	m_strShow += m_strSend;
	m_strShow += "\r\n";
	// �ѷ��͵������ÿ�
	m_strSend.Empty();
	UpdateData(FALSE);
}


void CDlgOne2One::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ShowWindow(SW_HIDE);
	// CDialogEx::OnClose();
}

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	CDlgOne2One* pDlg = (CDlgOne2One*)lpParam;
	SOCKET client = pDlg->m_sClient;
	CString strOne2One;
	pDlg->GetWindowText(strOne2One);
	CString strTemp = strOne2One + L":";
	CString strBuf;
	CDlgChatMain *pParent = (CDlgChatMain*)pDlg->GetParent();
	int nPos = pDlg->m_FilePath.ReverseFind('\\');
	CString fileName = pDlg->m_FilePath.Right(pDlg->m_FilePath.GetLength() - nPos - 1);
	strOne2One += L":" + fileName;
	CStringA str = CW2A(strOne2One.GetBuffer(), CP_THREAD_ACP);
	pParent->m_pClient->Send(FILETRANS, str.GetBuffer(), str.GetLength() + 1, client);
	std::fstream file;
	TCHAR* filePath = pDlg->m_FilePath.GetBuffer();
	file.open(filePath, std::ios::in | std::ios::binary);
	if (file.is_open())
		MessageBox(NULL, L"�򿪳ɹ�", L"FASDF", MB_OK);
	char buf[1024] = {};
	//��ʾ���Լ��ĶԻ�����
	while (!file.eof())
	{
		strBuf = strTemp;
		file.read(buf, 1024);
		strBuf += buf;
		str = CW2A(strBuf.GetBuffer(), CP_THREAD_ACP);
		pParent->m_pClient->Send(FILETRANS, str.GetBuffer(), str.GetLength() + 1, client);
		Sleep(50);
	}
	strBuf = strTemp;
	strBuf += "over";
	str = CW2A(strBuf.GetBuffer(), CP_THREAD_ACP);
	pParent->m_pClient->Send(FILETRANS, str.GetBuffer(), str.GetLength() + 1, client);
	MessageBox(NULL, L"���ͳɹ���", L"��ʾ", MB_OK);
	return TRUE;
}

void CDlgOne2One::OnBnClickedButtonSendfile()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static TCHAR BASED_CODE szFilter[] = _T("JPG (*.jpg)|*.jpg|")
		_T("BMP�ļ� (*.bmp)|*.bmp|")
		_T("PNG�ļ� (*.png)|*.png|")
		_T("All Files(*.*)|*.*||");

	CFileDialog Filedlg(TRUE, _T(""), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);
	if (Filedlg.DoModal() != IDOK)
	{
		return;
	}
	m_strSend = Filedlg.GetPathName();
	UpdateData(FALSE);

// 	UpdateData(TRUE);
// 	if (m_FilePath.IsEmpty())
// 	{
// 		return;
// 	}
// 	fileThread = AfxBeginThread((AFX_THREADPROC)ThreadProc, (LPVOID)this);
// 	WaitForSingleObject(fileThread, -1);
}


void CDlgOne2One::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UINT count;
	TCHAR filePath[MAX_PATH] = { 0 };

	count = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	if (count == 1) // �϶�һ���ļ�
	{
		DragQueryFile(hDropInfo, 0, filePath, sizeof(filePath));
		m_strSend = filePath;
		UpdateData(FALSE);
		DragFinish(hDropInfo);

		CDialogEx::OnDropFiles(hDropInfo);
		return;
	}
	else // ����ļ�
	{
		for (UINT i = 0; i < count; ++i)
		{
			int pathLen = DragQueryFile(hDropInfo, i, filePath, sizeof(filePath));
			m_strSend = filePath;
		}
		UpdateData(FALSE);
		DragFinish(hDropInfo);
	}

	CDialogEx::OnDropFiles(hDropInfo);
}
