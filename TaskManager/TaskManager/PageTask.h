#pragma once
#include "afxcmn.h"


// CPageTask �Ի���

class CPageTask : public CDialogEx
{
	DECLARE_DYNAMIC(CPageTask)

public:
	CPageTask(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPageTask();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE_TASK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Task;
	virtual BOOL OnInitDialog();
};

