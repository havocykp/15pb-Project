// DlgSearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Chatclient.h"
#include "DlgSearch.h"
#include "afxdialogex.h"
#include "CclientSocket.h"


// CDlgSearch �Ի���

IMPLEMENT_DYNAMIC(CDlgSearch, CDialogEx)

CDlgSearch::CDlgSearch(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSearch::IDD, pParent)
	, m_strSearch(_T(""))
{

}

CDlgSearch::~CDlgSearch()
{
}

void CDlgSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_strSearch);
	DDX_Control(pDX, IDC_LIST_FRIEND, m_listFriend);
}


BEGIN_MESSAGE_MAP(CDlgSearch, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CDlgSearch::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgSearch ��Ϣ�������


// void CDlgSearch::InsertFriend(CHATUPDATEUSER& objUpdate)
// {
// 	m_listFriend.InsertItem(0, CA2W(objUpdate.buf));
// }

void CDlgSearch::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CDialogEx::OnOK();
}
