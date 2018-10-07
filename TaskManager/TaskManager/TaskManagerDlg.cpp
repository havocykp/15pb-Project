
// TaskManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TaskManager.h"
#include "TaskManagerDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_ICON_NOTIFY WM_USER+100
BOOL g_bWillExit = FALSE;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTaskManagerDlg �Ի���



CTaskManagerDlg::CTaskManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TASKMANAGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTaskManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MANAGE, m_tabCtrl);
}

BEGIN_MESSAGE_MAP(CTaskManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MANAGE, &CTaskManagerDlg::OnTcnSelchangeTabManage)
END_MESSAGE_MAP()


// CTaskManagerDlg ��Ϣ�������


// ��ȡ����ԱȨ��
BOOL IsAdmin(HANDLE hProcess)
{
	HANDLE hToken = NULL;
	OpenProcessToken(hProcess, TOKEN_QUERY, &hToken);

	TOKEN_ELEVATION_TYPE tokenType = TokenElevationTypeDefault; // ���ڽ�����������

	DWORD dwRetSize = 0; // ���ڽ��պ��������Ϣ���ֽ���

						 // 2. ��ѯ���������е�Ȩ������ֵ.( ���ֵ���¼��ǰ�������Ǻ�������( ϸ����17_Ȩ�޹���_���ƵĻ�ȡ.cpp ) )
	GetTokenInformation(hToken,
		TokenElevationType,// ��ȡ���Ƶĵ�ǰ�����ȼ�
		&tokenType,
		sizeof(tokenType),
		&dwRetSize // ���軺�������ֽ���
	);


	// �������Ƶ������������Ӧ����Ϣ
	if (TokenElevationTypeFull == tokenType) {
		// 3. ���������TokenElevationTypeFull , ��ӵ���������ϵ�����,���Ը���������κ���Ȩ
		printf("����Ա�˻�,��ӵ��ȫ����Ȩ��,���Ը���������κ���Ȩ\n");
		return TRUE;
	}
	// 4. �����������, ����Ҫ�Թ���Ա����������б�����. ���������Ե������ķ������ʣ�µ�����.
	else if (TokenElevationTypeDefault == tokenType) {
		printf("Ĭ���û�, ������һ����ͨ�û�, �����ǹر�UACʱ��¼�Ĺ���Ա�û�\n");

		// ����ϵͳ����IsUserAnAdmin, ��һ��ȷ������ͨ�û����ǹ���Ա�û�
		return IsUserAnAdmin();
	}
	else if (TokenElevationTypeLimited == tokenType) {

		// �ж������Ƶ��û��ǹ���Ա
		// ����ǹ���Ա, ����������лᱣ���й���Ա��SID

		// 1. ��ȡϵͳ�ڼ�����Ա�û���SID
		SID adminSid;
		DWORD dwSize = sizeof(adminSid);
		CreateWellKnownSid(WinBuiltinAdministratorsSid, // ��ȡSID������,������ϵͳ�ڼ�����Ա
			NULL, // ��NULL,��ȡ���ؼ�����Ĺ���Ա
			&adminSid,// ��������Ĺ���ԱSID
			&dwSize // ����ṹ�Ĵ�С,Ҳ��Ϊ���
		);

		// ��ȡ�����Ƶ���������(�����Ƶ����ƶ�����һ�����ӵ�����,�����Ƶ�������ʽ����������������. )
		TOKEN_LINKED_TOKEN linkToken;
		GetTokenInformation(hToken,
			TokenLinkedToken, // ��ȡ���ӵ����ƾ��
			&linkToken,
			sizeof(linkToken),
			&dwSize
		);

		// �����ӵ������в����Ƿ���й���Ա��SID
		BOOL    bIsContain = FALSE; // ���ڱ����Ƿ����.
		CheckTokenMembership(linkToken.LinkedToken, // ����������м��
			&adminSid,             // ����������Ƿ������SID
			&bIsContain);           // ���TRUE�����,��֮������

		if (bIsContain) {
			printf("Ȩ�ޱ��˸�������ƹ���Ա�˻�, ����Ȩ�ޱ��ƴ���\n");
		}


		return FALSE; // �����Թ���ԱȨ������
	}

	return FALSE;
}

BOOL CTaskManagerDlg::OnInitDialog()
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	// ���̹���ʵ��
	// ʵ�����̹��ܣ���Ӧ����Ҽ�
	NOTIFYICONDATA m_tnid;

	m_tnid.cbSize = sizeof(NOTIFYICONDATA); // ���ýṹ��С
	m_tnid.hWnd = this->m_hWnd; // ����ͼ���Ӧ�Ĵ���
	m_tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP; // ͼ������
	m_tnid.uCallbackMessage = WM_ICON_NOTIFY; // Ӧ�ó�����Ļص���ϢID

	CString szToolTip;
	szToolTip = _T("Task �ͻ��˳���");
	_tcscpy_s(m_tnid.szTip, szToolTip); // ������Ϣ
	m_tnid.uID = IDR_MAINFRAME; // Ӧ�ó���ͼ��
	m_tnid.hIcon = m_hIcon; // ͼ����
	PNOTIFYICONDATA m_ptnid = &m_tnid;
	::Shell_NotifyIcon(NIM_ADD, m_ptnid); // ����ͼ�굽ϵͳ��

	//��Ȩ����
// 	 	HANDLE hToken;
// 	 	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
// 	 	{
// 	 		TOKEN_PRIVILEGES tp;
// 	 		tp.PrivilegeCount = 1;
// 	 		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
// 	 		if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid))
// 	 		{
// 	 			AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
// 	 		}
// 	 		CloseHandle(hToken);
// 	 	}

	//��һ����Ȩ����

	if (!IsAdmin(GetCurrentProcess())) {

		// �Թ���Ա������б�����
		//  1 ��ȡ�����̵��ļ�·��.
		TCHAR path[MAX_PATH] = { 0 }; // ��Ҫ��ʼ��
		DWORD dwPathSize = MAX_PATH;
		QueryFullProcessImageName(GetCurrentProcess(), 0, path, &dwPathSize);

		// 2 ���ô������̵�API���б�����.
		ShellExecute(NULL,   // ���ھ��,û������NULL
			_T("runas"),     // �Թ���Ա������е���Ҫ����
			path,            // �������еĳ����·��(�����Ǳ�����)
			NULL,            // �����в���
			NULL,            // �½��̵Ĺ���Ŀ¼��·��
			SW_SHOW          // ���������ʾ��־(��С��,���, ��ʾ,���ص�)
		);

		// �˳�������
		//exit(0);
		ExitProcess(0);
	}

	LUID privilegeLuid;
	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &privilegeLuid);

	//��ȡ����������
	HANDLE hToken = NULL;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);

	TOKEN_PRIVILEGES tokenPrivieges;
	// ʹ����Ȩ��LUID����ʼ���ṹ��.
	tokenPrivieges.PrivilegeCount = 1; // ��Ȩ����
	tokenPrivieges.Privileges[0].Luid = privilegeLuid; // ����ȨLUID���浽������
	tokenPrivieges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;// ������ֵ��Ϊ����(�н���,�Ƴ�������״̬)

	AdjustTokenPrivileges(hToken,              // Ҫ�����Ȩ������
		FALSE,               // TRUE���Ƴ���Ȩ, FALSE�������Ȩ
		&tokenPrivieges,     // Ҫ��ӵ���Ȩ����
		sizeof(tokenPrivieges),// ������Ȩ����Ĵ�С
		NULL,                // �ɵ���Ȩ����
		NULL                  // �ɵ���Ȩ����ĳ���
	);


	// ����Tab�ؼ���ǩ
	m_tabCtrl.InsertItem(0, _T("Ӧ�ó���"));
	m_tabCtrl.InsertItem(1, _T("����"));
	m_tabCtrl.InsertItem(2, _T("����"));

	// ��������
	m_tabCtrl.SetPadding(19);
	m_tabCtrl.SetMinTabWidth(50);
	m_tabCtrl.SetItemSize(CSize(50, 25));

	// ���ӶԻ����ںϽ�Tab
	m_task.Create(IDD_PAGE_TASK, &m_tabCtrl);
	m_proc.Create(IDD_PAGE_PROCESS, &m_tabCtrl);
	m_chart.Create(IDD_PAGE_CHART, &m_tabCtrl);

	//	�趨��Tab����ʾ�ķ�Χ
	CRect rc;
	m_tabCtrl.GetClientRect(rc);
	rc.top += 25;
	// 	rc.bottom -= 8;
	// 	rc.left += 8;
	// 	rc.right -= 8;
	m_task.MoveWindow(&rc);
	m_proc.MoveWindow(&rc);
	m_chart.MoveWindow(&rc);

	// �ѶԻ������ָ�뱣������
	m_pDialog[0] = &m_task;
	m_pDialog[1] = &m_proc;
	m_pDialog[2] = &m_chart;

	// ��ʾ��ʼҳ��
	m_pDialog[0]->ShowWindow(SW_SHOW);
	m_pDialog[1]->ShowWindow(SW_HIDE);
	m_pDialog[2]->ShowWindow(SW_HIDE);

	// ���浱ǰѡ��
	m_CurSelTab = 0;

	UpdateData(FALSE);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTaskManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTaskManagerDlg::OnPaint()
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
HCURSOR CTaskManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ʵ�ֶԻ�����л�
void CTaskManagerDlg::OnTcnSelchangeTabManage(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_pDialog[m_CurSelTab]->ShowWindow(SW_HIDE);
	m_CurSelTab = m_tabCtrl.GetCurSel();
	if (m_pDialog[m_CurSelTab]) {
		m_pDialog[m_CurSelTab]->ShowWindow(SW_SHOW);
	}

	*pResult = 0;
}


// ����رպ��Զ��Ƴ�����ͼ��
void CTaskManagerDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	// �˳��߳�
	g_bWillExit = TRUE;

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

// ������Ӧ����ʵ��
// ���̣��ָ�����
void CTaskManagerDlg::OnTrayRestore()
{
	// TODO: �ڴ���������������

	AfxGetApp()->m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
	SetForegroundWindow();
}


void CTaskManagerDlg::OnTrayExit()
{
	// TODO: �ڴ���������������
	OnClose();
}