
// A1Pack BaseDlg.h : ͷ�ļ�
//

#pragma once
#define A1PACK_BASE_EXPORTS
#include "../A1Pack_Base/A1Pack_Base.h"

#ifdef _DEBUG
#pragma comment(lib, "../Debug/A1Pack_Base.lib")
#else
#pragma comment(lib, "../Release/A1Pack_Base.lib")
#endif

// CA1PackBaseDlg �Ի���
class CA1PackBaseDlg : public CDialogEx
{
// ����
public:
	CA1PackBaseDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_A1PACKBASE_DIALOG };
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
	afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSelect();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedShowMsg();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	CString m_strPath;
	BOOL m_bShowMsg;
};
