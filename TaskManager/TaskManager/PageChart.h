#pragma once
#include "afxcmn.h"


// CPageChart �Ի���

class CPageChart : public CDialogEx
{
	DECLARE_DYNAMIC(CPageChart)

public:
	CPageChart(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPageChart();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE_CHART };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_Chart;
	virtual BOOL OnInitDialog();
};
