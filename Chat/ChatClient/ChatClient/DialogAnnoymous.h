#pragma once


// CDialogAnnoymous �Ի���

class CDialogAnnoymous : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogAnnoymous)

public:
	CDialogAnnoymous(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogAnnoymous();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ANNOYMOUS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
