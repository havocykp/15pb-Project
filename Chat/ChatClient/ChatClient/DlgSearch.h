#pragma once
#include "afxcmn.h"


// CDlgSearch �Ի���

class CDlgSearch : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSearch)

public:
	CDlgSearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSearch();

// �Ի�������
	enum { IDD = IDD_DIALOGSEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//void InsertFriend(CHATUPDATEUSER& objUpdate);
	CString m_strSearch;
	afx_msg void OnBnClickedOk();
	CListCtrl m_listFriend;
};
