
// SecurityGuard.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "SecurityGuard.h"
#include "MainDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// ����Ȩ�޵Ĵ���

BOOL    IsAdmin(HANDLE hProcess)
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

// CApp

BEGIN_MESSAGE_MAP(CApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CApp ����

CApp::CApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CApp ����

CApp theApp;


// CApp ��ʼ��

BOOL CApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	//��Ȩ����
	// 	HANDLE hToken;
	// 	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
	// 	{
	// 		TOKEN_PRIVILEGES tp;
	// 		tp.PrivilegeCount = 1;
	// 		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	// 		if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid))
	// 		{
	// 			AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
	// 		}
	// 		CloseHandle(hToken);
	// 	}

	//��һ����Ȩ����

// 	if (!IsAdmin(GetCurrentProcess())) {
// 
// 		// �Թ���Ա������б�����
// 		//  1 ��ȡ�����̵��ļ�·��.
// 		TCHAR path[MAX_PATH] = { 0 }; // ��Ҫ��ʼ��
// 		DWORD dwPathSize = MAX_PATH;
// 		QueryFullProcessImageName(GetCurrentProcess(), 0, path, &dwPathSize);
// 
// 		// 2 ���ô������̵�API���б�����.
// 		ShellExecute(NULL,            // ���ھ��,û������NULL
// 			_T("runas"),   // �Թ���Ա������е���Ҫ����
// 			path,            // �������еĳ����·��(�����Ǳ�����)
// 			NULL,            // �����в���
// 			NULL,            // �½��̵Ĺ���Ŀ¼��·��
// 			SW_SHOW           // ���������ʾ��־(��С��,���, ��ʾ,���ص�)
// 		);
// 
// 		// �˳�������
// 		//exit(0);
// 		ExitProcess(0);
// 	}
// 
// 
// 	LUID privilegeLuid;
// 	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &privilegeLuid);
// 
// 	//��ȡ����������
// 	HANDLE hToken = NULL;
// 	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
// 
// 	TOKEN_PRIVILEGES tokenPrivieges;
// 	// ʹ����Ȩ��LUID����ʼ���ṹ��.
// 	tokenPrivieges.PrivilegeCount = 1; // ��Ȩ����
// 	tokenPrivieges.Privileges[0].Luid = privilegeLuid; // ����ȨLUID���浽������
// 	tokenPrivieges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;// ������ֵ��Ϊ����(�н���,�Ƴ�������״̬)
// 
// 	AdjustTokenPrivileges(hToken,              // Ҫ�����Ȩ������
// 		FALSE,               // TRUE���Ƴ���Ȩ, FALSE�������Ȩ
// 		&tokenPrivieges,     // Ҫ��ӵ���Ȩ����
// 		sizeof(tokenPrivieges),// ������Ȩ����Ĵ�С
// 		NULL,                // �ɵ���Ȩ����
// 		NULL                  // �ɵ���Ȩ����ĳ���
// 	);

	CMainDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

#ifndef _AFXDLL
	ControlBarCleanUp();
#endif

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

