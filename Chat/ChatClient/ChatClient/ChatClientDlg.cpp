
// ChatclientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chatclient.h"
#include "ChatclientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatclientDlg �Ի���
#define WM_ICON_NOTIFY WM_USER + 100


CChatclientDlg::CChatclientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatclientDlg::IDD, pParent)
	, m_strName(_T(""))
	, m_strPass(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatclientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_strName, m_strName);
	DDX_Text(pDX, IDC_EDIT_strPass, m_strPass);
}

BEGIN_MESSAGE_MAP(CChatclientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Anony, &CChatclientDlg::OnBtnProcAnony)
	ON_BN_CLICKED(IDC_BUTTON_Register, &CChatclientDlg::OnBtnProcRegister)
	ON_BN_CLICKED(IDC_BUTTON_Login, &CChatclientDlg::OnBtnProcLogin)
	ON_BN_CLICKED(IDC_CHECK_SAVEPWD, &CChatclientDlg::OnBnClickedCheckSavepwd)
	ON_BN_CLICKED(IDC_CHECK_AUTO, &CChatclientDlg::OnBnClickedCheckAuto)
	ON_WM_CLOSE()
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)
	ON_COMMAND(ID_TRAY_32777, &CChatclientDlg::OnTrayRestore)
	ON_COMMAND(ID_TRAY_32778, &CChatclientDlg::OnTrayExit)
	//ON_BN_CLICKED(IDC_BUTTON1, &CChatclientDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CChatclientDlg ��Ϣ�������

BOOL CChatclientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	NOTIFYICONDATA m_tnid;
	m_tnid.cbSize = sizeof(NOTIFYICONDATA);
	m_tnid.hWnd = this->m_hWnd;
	m_tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	m_tnid.uCallbackMessage = WM_ICON_NOTIFY;

	CString szToolTip;
	szToolTip = _T("������ �ͻ��˳���");
	_tcscpy_s(m_tnid.szTip, szToolTip);
	m_tnid.uID = IDR_MAINFRAME;
	m_tnid.hIcon = m_hIcon;
	PNOTIFYICONDATA m_ptnid = &m_tnid;
	::Shell_NotifyIcon(NIM_ADD, m_ptnid); // ����ϵͳ����

	// ����ͼƬ
	m_BKGround.LoadBitmapW(IDB_BITMAP_WINMAIN);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CChatclientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
	if (nID == SC_MINIMIZE)
	{
		ShowWindow(FALSE); // ���ش���
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CChatclientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);
		CBitmap bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP_WINMAIN);
		BITMAP bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap *pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CChatclientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatclientDlg::OnBtnProcAnony()
{
	//TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!m_client.ConnectSrver("127.0.0.1", 1234))
	{
		MessageBox(L"���ӷ�����ʧ�ܣ�", L"Error!", MB_OK | MB_ICONWARNING);
		return;
	}

	// ���ص�¼����
	ShowWindow(SW_HIDE);
	// ��ʾ�������촰��
	CDlgChatMain dlgChat(&m_client);   // �����Զ���Ĺ��캯��

	dlgChat.DoModal();
	m_client.Close();
	// �˳�
	CChatclientDlg::OnClose();
}


void CChatclientDlg::OnBtnProcRegister()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ�û���������
	UpdateData(TRUE);

	if (m_strName.IsEmpty() || m_strPass.IsEmpty())
	{
		MessageBox(L"�û���/���벻��Ϊ��!");
		return;
	}

	if (!m_client.ConnectSrver("127.0.0.1", 1234))
	{
		MessageBox(L"���ӷ�����ʧ��!", L"Error!", MB_OK | MB_ICONWARNING);
		return;
	}

	// ע���û���:����
	CString strSend = m_strName;
	strSend += L":" + m_strPass;

	CStringA str = CW2A(strSend.GetBuffer(), CP_THREAD_ACP);
	m_client.Send(REGISTER, str.GetBuffer(), str.GetLength() + 1);

	// ֱ�ӵȴ�ע����
	char* ret = m_client.Recv();
	if (ret == nullptr)
	{
		MessageBox(L"ע��ʧ��!");
	}
	else
	{
		MessageBox(L"ע��ɹ���");
	}

	m_client.Close();

	return;
}


void CChatclientDlg::OnBtnProcLogin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// ��ȡ�û���������
	UpdateData(TRUE);
	if (m_strName.IsEmpty() || m_strPass.IsEmpty())
	{
		MessageBox(L"�û���/���벻��Ϊ��!");
		return;
	}

	if (!m_client.ConnectSrver("127.0.0.1", 1234))
	{
		MessageBox(L"���ӷ�����ʧ��!", L"Error", MB_OK | MB_ICONWARNING);
		return;
	}

	// ��¼�û���: ����
	CString strSend = m_strName;
	strSend += L":" + m_strPass;
	CStringA str = CW2A(strSend.GetBuffer(), CP_THREAD_ACP);
	m_client.Send(LOGIN, str.GetBuffer(), str.GetLength() + 1);
	char* ret = m_client.Recv();

	if (ret == nullptr)
	{
		MessageBox(L"��¼ʧ��!");
		m_client.Close();
		return;
	}

	// ��¼�ɹ�
	// ���õ�ǰ��¼�û���,������ʾ���Ǹ��������
	CStringA strShowName = CW2A(m_strName.GetBuffer(), CP_THREAD_ACP);
	strcpy_s(m_client.m_szName, strShowName.GetBuffer());
	// ���ص�¼����
	ShowWindow(SW_HIDE);

	// ��ʾ���촰��
	CDlgChatMain dlgChat(&m_client);
	dlgChat.m_bLogin = TRUE;   // ������ģʽ
	dlgChat.DoModal();
	m_client.Close();

	CChatclientDlg::OnClose();
}


void CChatclientDlg::OnBnClickedCheckSavepwd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (!m_bSavePwd)
	{
		if (m_bAuto)
		{
			m_bAuto = FALSE;
			UpdateData(FALSE);
		}
	}
}


void CChatclientDlg::OnBnClickedCheckAuto()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_bAuto)
	{
		if (!m_bSavePwd)
		{
			m_bSavePwd = TRUE;
			UpdateData(FALSE);
		}
	}
}


void CChatclientDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	NOTIFYICONDATA nd = { 0 };
	nd.cbSize = sizeof(NOTIFYICONDATA);
	nd.hWnd = m_hWnd;
	nd.uID = IDR_MAINFRAME;
	nd.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nd.uCallbackMessage = WM_ICON_NOTIFY;
	nd.hIcon = m_hIcon;
	Shell_NotifyIcon(NIM_DELETE, &nd);

	CDialogEx::OnClose();
}

LRESULT CChatclientDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_LBUTTONDOWN:
	{
		AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
		SetForegroundWindow();
		break;
	}
	case WM_RBUTTONUP:
	{
		POINT point;
		HMENU hMenu, hSubMenu;
		GetCursorPos(&point); // ���λ��
		hMenu = LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENU_TRAY));
		hSubMenu = GetSubMenu(hMenu, 0);
		SetForegroundWindow();

		TrackPopupMenu(hSubMenu, 0, point.x, point.y, 0, m_hWnd, NULL);
	}
	}
	return 1;
}


void CChatclientDlg::OnTrayRestore()
{
	// TODO: �ڴ���������������
	AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
	SetForegroundWindow();
}


void CChatclientDlg::OnTrayExit()
{
	// TODO: �ڴ���������������
	OnClose();
}


// void CChatclientDlg::OnBnClickedButton1()
// {
// 	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	//ShellExecute(0, _T("open"), _T("Notepad++"), _T("D:\\Notepad++"), _T(""), SW_SHOW);
// }
