#pragma once
#include "afxcmn.h"


// CPageProc �Ի���

class CPageProc : public CDialogEx
{
	DECLARE_DYNAMIC(CPageProc)

public:
	CPageProc(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPageProc();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE_PROCESS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Proc;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMRClickListProc(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_strSelectedTopic;
	afx_msg void OnLvnColumnclickListProc(NMHDR *pNMHDR, LRESULT *pResult);

	static DWORD m_SortColum;
	static BOOL m_bAs;
	static int CALLBACK MyListCompar(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
};

