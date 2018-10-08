
// ChatclientDlg.h : ͷ�ļ�
//

#pragma once
#include "CclientSocket.h"
#include "DlgChatMain.h"

// CChatclientDlg �Ի���
class CChatclientDlg : public CDialogEx
{
// ����
public:
	CChatclientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHATCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CclientSocket m_client;
	CString m_strName;
	CString m_strPass;
	afx_msg void OnBtnProcAnony();
	afx_msg void OnBtnProcRegister();
	afx_msg void OnBtnProcLogin();
	bool m_bSavePwd;
	bool m_bAuto;
	CBitmap m_BKGround;
	afx_msg void OnBnClickedCheckSavepwd();
	afx_msg void OnBnClickedCheckAuto();
	afx_msg void OnClose();
	LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTrayRestore();
	afx_msg void OnTrayExit();
	//afx_msg void OnBnClickedButton1();
};
