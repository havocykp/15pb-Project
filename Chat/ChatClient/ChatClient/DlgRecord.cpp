// DlgRecord.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chatclient.h"
#include "DlgRecord.h"
#include "afxdialogex.h"
#include "DlgChatMain.h"

// CDlgRecord �Ի���

IMPLEMENT_DYNAMIC(CDlgRecord, CDialogEx)

CDlgRecord::CDlgRecord(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgRecord::IDD, pParent)
{

}

CDlgRecord::~CDlgRecord()
{
}

void CDlgRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Record, m_listRecord);
}


BEGIN_MESSAGE_MAP(CDlgRecord, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CDlgRecord ��Ϣ�������


BOOL CDlgRecord::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_listRecord.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listRecord.InsertColumn(0, L"from", 0, 50);
	m_listRecord.InsertColumn(1, L"to", 0, 50);
	m_listRecord.InsertColumn(2, L"content", 0, 300);
	UpdateList();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CDlgRecord::UpdateList()
{
	// ɾ��֮ǰ�������¼
	m_listRecord.DeleteAllItems();
	CDlgChatMain* pParent = (CDlgChatMain*)GetParent();
	auto& vec = pParent->m_pClient->m_vecMsgRecord;
	DWORD dwCount = vec.size();
	CString strTemp;
	for (DWORD i = 0; i < dwCount; i++)
	{
		// ���췢��
		strTemp = vec[i].szFrom;
		m_listRecord.InsertItem(i, strTemp.GetBuffer());
		// ������շ�
		strTemp = vec[i].szTo;
		m_listRecord.SetItemText(i, 1, strTemp.GetBuffer());
		// ��������
		strTemp = vec[i].szContent;
		m_listRecord.SetItemText(i, 2, strTemp.GetBuffer());
	}
}

void CDlgRecord::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnClose();
}
