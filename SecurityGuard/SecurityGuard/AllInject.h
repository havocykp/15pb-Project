#pragma once


// CAllInject �Ի���

class CAllInject : public CDialogEx
{
	DECLARE_DYNAMIC(CAllInject)

public:
	CAllInject(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAllInject();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Inject };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
