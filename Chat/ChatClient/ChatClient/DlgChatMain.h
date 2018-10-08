#pragma once

#include "CclientSocket.h"
#include "afxcmn.h"
#include "DlgOne2One.h"
#include "DlgSearch.h"
#include "DlgRecord.h"
// CDlgChatMain �Ի���

class CDlgChatMain : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgChatMain)

public:
#define WM_MYSOCKET WM_USER+100
	CDlgChatMain(CWnd* pParent = NULL);   // ��׼���캯��
	CDlgChatMain(CclientSocket* pClient, CWnd* pParent = NULL);
	virtual ~CDlgChatMain();

// �Ի�������
	enum { IDD = IDD_DLGANONYMOUS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnProcSend();
	virtual void OnOK();
	afx_msg void OnNMRDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnAddfriend();
	afx_msg void OnSearch();
	afx_msg void OnGetchatrecord();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

public:
	// ��¼���컹����������
	BOOL m_bLogin ;
	CclientSocket* m_pClient;
	CString m_strShow;
	CString m_strSend;
	CListCtrl m_listName;
	map<CString,CDialogEx*> m_map;
	DWORD m_dwNameIndex;
	CDlgRecord* m_pDlgRecord = nullptr;
protected:
	afx_msg LRESULT OnMysocket(WPARAM wParam, LPARAM lParam);
	void InsertOrDeleteUser(CHATUPDATEUSER& objUpdate);
	void ChatForOne2One(CHATONE2ONE& objOne2One);
public:
	afx_msg void OnNMDblcList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
};
