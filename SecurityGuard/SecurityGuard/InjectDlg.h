#pragma once


// CInjectDlg �Ի���

class CInjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInjectDlg)

public:
	CInjectDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInjectDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INJECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
