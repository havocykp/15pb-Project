
// TaskManagerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "PageChart.h"
#include "PageProc.h"
#include "PageTask.h"


// CTaskManagerDlg �Ի���
class CTaskManagerDlg : public CDialogEx
{
// ����
public:
	CTaskManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TASKMANAGER_DIALOG };
#endif

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
	CTabCtrl m_tabCtrl;
	CPageProc m_proc;
	CPageTask m_task;
	CPageChart m_chart;
#define MAX_DLG_PAGE 5
	CDialog *m_pDialog[MAX_DLG_PAGE];
	int m_CurSelTab;
	afx_msg void OnTcnSelchangeTabManage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();
	afx_msg void OnTrayRestore();
	afx_msg void OnTrayExit();

};
