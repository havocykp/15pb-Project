#pragma once


// CDlgOne2One �Ի���
#include "DlgChatMain.h"

class CDlgOne2One : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOne2One)

public:
	CDlgOne2One(/*SOCKET sClient ,*/CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgOne2One();

// �Ի�������
	enum { IDD = IDD_DLGONE2ONE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strShow;       // ����༭��	
	CString m_strSend;       // ���ͱ༭��
	CString m_strTitle;      // ����
	SOCKET m_sClient;
	CString m_FilePath;
	HANDLE fileThread;
	afx_msg void OnBtnProcSend();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButtonSendfile();
	
	afx_msg void OnDropFiles(HDROP hDropInfo);
};
