// DlgChatMain.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chatclient.h"
#include "DlgChatMain.h"
#include "afxdialogex.h"


// CDlgChatMain �Ի���

IMPLEMENT_DYNAMIC(CDlgChatMain, CDialogEx)

CDlgChatMain::CDlgChatMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgChatMain::IDD, pParent)
	, m_strShow(_T(""))
	, m_strSend(_T(""))
{

}

CDlgChatMain::~CDlgChatMain()
{
}

void CDlgChatMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_QULIAO, m_strShow);
	DDX_Text(pDX, IDC_EDIT_FASONG, m_strSend);
	DDX_Control(pDX, IDC_LIST_Anonymous, m_listName);
}

void CDlgChatMain::ChatForOne2One(CHATONE2ONE& objOne2One)
{
	CString strName(objOne2One.szName);
	CString strContent(objOne2One.szContent);

	if (m_map.find(strName) == m_map.end())
	{
		// ����˽�Ĵ���
		CDlgOne2One* pDlg = new CDlgOne2One;
		pDlg->Create(IDD_DLGONE2ONE, this);
		pDlg->SetWindowTextW(strName.GetBuffer());
		m_map[strName] = pDlg;
		pDlg->m_strShow += strName + L":" + strContent;
		pDlg->m_strShow += "\r\n";
		pDlg->UpdateData(FALSE);
		pDlg->ShowWindow(SW_SHOW);
	}
	else
	{
		CDlgOne2One* pDlg = (CDlgOne2One*)m_map[strName];
		pDlg->UpdateData(TRUE);
		pDlg->m_strShow += strName + L":" + strContent;
		pDlg->m_strShow += "\r\n";
		pDlg->UpdateData(FALSE);
		pDlg->ShowWindow(SW_SHOW);
	}

}

BEGIN_MESSAGE_MAP(CDlgChatMain, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CDlgChatMain::OnBtnProcSend)
	ON_NOTIFY(NM_RDBLCLK, IDC_LIST_Anonymous, &CDlgChatMain::OnNMRDblclkList1)
	ON_COMMAND(ID_AddFriend, &CDlgChatMain::OnAddfriend)
	ON_COMMAND(ID_Search, &CDlgChatMain::OnSearch)
	ON_COMMAND(ID_GetChatRecord, &CDlgChatMain::OnGetchatrecord)
	ON_WM_TIMER()
	ON_MESSAGE(WM_MYSOCKET, &CDlgChatMain::OnMysocket)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_Anonymous, &CDlgChatMain::OnNMRClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_Anonymous, &CDlgChatMain::OnNMDblcList1)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgChatMain ��Ϣ�������

CDlgChatMain::CDlgChatMain(CclientSocket* pClient, CWnd* pParent /*= NULL*/)
	:CDialogEx(IDD_DLGANONYMOUS, pParent), m_pClient(pClient)
{

}

BOOL CDlgChatMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	// ���ô��ڱ���Ϊ�û��ǳ�
	// ������¼ʱm_pClient->m_szName�Ǹ����ֵ�����캯���ڳ�ʼ��
	// ��¼��ʱ���ǵ�¼�û��������¼��ť��ʱ���ʼ��
	CString strTitle(m_pClient->m_szName);
	SetWindowText(strTitle.GetBuffer());
	// ���ô����������ɼ�
	ModifyStyleEx(0, WS_EX_APPWINDOW);
	// �����û��б�
	m_listName.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listName.InsertColumn(0, L"�����б�", 0, 100);
	// ʹ����Ϣѡ��ģ�Ͱ�socket�͵�ǰ�Ի���
	// 1.define �Զ�����ϢWM_SOCKET
	// 2.��������Զ�����Ϣ(WM_SOCKET)��Ӧ
	// 3.WSAAsynSelect��socket�����ں���Ϣ
	WSAAsyncSelect(m_pClient->m_sClient, m_hWnd, WM_MYSOCKET, FD_READ | FD_CLOSE);
	// ���߷������Լ����ǳ�
	m_pClient->Send(ANONYMOUS, m_pClient->m_szName, strlen(m_pClient->m_szName) + 1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void CDlgChatMain::OnBtnProcSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_strSend.IsEmpty())
	{
		// ������͵ı༭�����ǿ�,�Ͳ�����
		return;
	}
	CStringA str = CW2A(m_strSend.GetBuffer(), CP_THREAD_ACP);
	m_pClient->Send(CHAT, str.GetBuffer(), str.GetLength() + 1);
	// ��ʾ���Լ��ĶԻ�����
	m_strShow += "��˵:";
	m_strShow += m_strSend;
	m_strShow += "\r\n";

	// �ѷ��������ÿ�
	m_strSend.Empty();
	UpdateData(FALSE);
}


void CDlgChatMain::OnOK()
{
	// TODO:  �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
}


void CDlgChatMain::OnNMRDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	// ˫���Ŀհ�����
	if (pNMItemActivate->iItem == -1)
		return;
	// �½�1V1����Ի���
	CDlgOne2One* pDlg = new CDlgOne2One;
	pDlg->Create(IDD_DLGONE2ONE, this);   //�ѵ�ǰ����ָ��Ϊ˽�Ĵ��ڵĸ�����

	// ���ô��ڱ���ΪҪ�����Ŀ���û�����
	CString strTitle = m_listName.GetItemText(pNMItemActivate->iItem, 0);
	pDlg->SetWindowTextW(strTitle.GetBuffer());

	// �Ѹ�˽�Ĵ�����ӵ��Լ���˽��MAP��
	m_map[strTitle] = pDlg;

	pDlg->ShowWindow(SW_SHOW);
}


void CDlgChatMain::OnAddfriend()
{
	// TODO:  �ڴ���������������
	CString strFriend = m_listName.GetItemText(m_dwNameIndex, 0);

	// ��ǰ�û�:Ҫ����û�
	CString strUserFrd;
	GetWindowText(strUserFrd);
	strUserFrd += L":";
	strUserFrd += strFriend;
	CStringA strSend = CW2A(strUserFrd.GetBuffer(), CP_THREAD_ACP);
	m_pClient->Send(ADDFRIEND, strSend.GetBuffer(), strSend.GetLength() + 1);
}


void CDlgChatMain::OnSearch()
{
	// TODO:  �ڴ���������������
	CDlgSearch dlgSearch;
	dlgSearch.DoModal();
	if (dlgSearch.m_strSearch.IsEmpty()) return;  // �����Ի���������༭�������
	CStringA strSearch = CW2A(dlgSearch.m_strSearch.GetBuffer(), CP_THREAD_ACP);
	m_pClient->Send(SEARCHUSER, strSearch.GetBuffer(), strSearch.GetLength() + 1);
}


void CDlgChatMain::OnGetchatrecord()
{
	// TODO:  �ڴ���������������
	m_pClient->m_hEvent = CreateEventW(NULL, FALSE, TRUE, L"Event1");
	// ��ֹ�ϴεĻ�ȡ��Ϣ��¼��δ���ؾ���������,�����¼�����ͬ��
	DWORD dwRet = WaitForSingleObject(m_pClient->m_hEvent, 100);
	if (dwRet == WAIT_FAILED || dwRet == WAIT_TIMEOUT) return;
	m_pClient->Send(MSGRECORD, NULL, NULL);
	m_pClient->m_vecMsgRecord.clear();
	// ���ö�ʱ���ȴ���Ϣ����
	SetTimer(0x1001, 1000, NULL);
}


void CDlgChatMain::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (nIDEvent == 0x1001)
	{
		// �ȴ���Ϣ��¼����,��Ϣ��¼����¼�������Ϊ��true
		DWORD dwRet = WaitForSingleObject(m_pClient->m_hEvent, 100);
		if (dwRet == WAIT_OBJECT_0)
		{
			// ��ʾ�´���
			if (m_pDlgRecord)
			{
				// ��������
				m_pDlgRecord->UpdateList();
				// ��ʾ����
				m_pDlgRecord->ShowWindow(SW_SHOW);
				KillTimer(nIDEvent);
				SetEvent(m_pClient->m_hEvent);
			}
			else
			{
				m_pDlgRecord = new CDlgRecord;
				m_pDlgRecord->Create(IDD_DIALOGRECORD, this);
				m_pDlgRecord->ShowWindow(SW_SHOW);
			}
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


afx_msg LRESULT CDlgChatMain::OnMysocket(WPARAM wParam, LPARAM lParam)
{
	// wparam ��socket
	// lparam ��word���¼�
	// lparam ��word�Ǵ�����
	SOCKET s = wParam;
	WORD wEvent = WSAGETSELECTEVENT(lParam);
	WORD wErrorCode = WSAGETSELECTERROR(lParam);

	// ���ж��Ƿ�����������¼�����,��������
	if (wErrorCode)
	{
		exit(0);
		MessageBox(L"�������! ");
		CDialogEx::OnClose();
	}

	switch (wEvent)
	{
	case FD_READ:
	{
		char* szRecv = m_pClient->Recv();
		if (szRecv == nullptr)
		{
			if (m_pClient->m_pObjUpdate)
			{
				// �����û��б��õ�
				// �ж��û��Ǽ��뻹���˳�
				// RecvForUpdateUserlist�������ش���
				InsertOrDeleteUser(*m_pClient->m_pObjUpdate);
				delete m_pClient->m_pObjUpdate;
				m_pClient->m_pObjUpdate = nullptr;
			}
			else if (m_pClient->m_pObjOne20ne)
			{
				// 1V1�����õ�
				// RecvForOne2One�������ش���
				ChatForOne2One(*m_pClient->m_pObjOne20ne);
				delete m_pClient->m_pObjOne20ne;
				m_pClient->m_pObjOne20ne = nullptr;
			}
			return 0;
		}
		UpdateData(TRUE);
		m_strShow += szRecv;
		m_strShow += "\r\n";
		UpdateData(FALSE);
	}
	default:
		break;
	}

	return 0;
}

void CDlgChatMain::InsertOrDeleteUser(CHATUPDATEUSER& objUpdate)
{
	m_listName.InsertItem(0, CA2W(objUpdate.buf));
}

void CDlgChatMain::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	// ���������Ҽ�ʧ��
	if (!m_bLogin) return;
	// ��ǰ�������,���ڻ����ӵ����ĸ�����
	m_dwNameIndex = pNMItemActivate->iItem;
	// �����Ҽ��˵�
	CMenu mu;
	mu.LoadMenuW(IDR_MENU1);
	CMenu* pSub = mu.GetSubMenu(0);
	CPoint pt;
	GetCursorPos(&pt);
	pSub->TrackPopupMenu(TPM_LEFTALIGN, pt.x, pt.y, this, NULL);
}


void CDlgChatMain::OnNMDblcList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	// ˫���Ŀհ�����
	if (pNMItemActivate->iItem == -1)
		return;
	// �½�1V1����Ի���
	CDlgOne2One* pDlg = new CDlgOne2One;
	pDlg->Create(IDD_DLGONE2ONE, this);   //�ѵ�ǰ����ָ��Ϊ˽�Ĵ��ڵĸ�����

	// ���ô��ڱ���ΪҪ�����Ŀ���û�����
	CString strTitle = m_listName.GetItemText(pNMItemActivate->iItem, 0);
	pDlg->SetWindowTextW(strTitle.GetBuffer());

	// �Ѹ�˽�Ĵ�����ӵ��Լ���˽��MAP��
	m_map[strTitle] = pDlg;
	pDlg->ShowWindow(SW_SHOW);
}


void CDlgChatMain::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnClose();
	PostQuitMessage(WM_QUIT);
}

