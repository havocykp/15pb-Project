#pragma once
#include "afxcmn.h"



// CDlgRecord �Ի���

class CDlgRecord : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgRecord)

public:
	CDlgRecord(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgRecord();

// �Ի�������
	enum { IDD = IDD_DIALOGRECORD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listRecord;
	void UpdateList();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
};
