// PageChart.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TaskManager.h"
#include "PageChart.h"
#include "afxdialogex.h"


// CPageChart �Ի���

IMPLEMENT_DYNAMIC(CPageChart, CDialogEx)

CPageChart::CPageChart(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE_CHART, pParent)
{

}

CPageChart::~CPageChart()
{
}

void CPageChart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Chart, m_Chart);
}


BEGIN_MESSAGE_MAP(CPageChart, CDialogEx)
END_MESSAGE_MAP()


// CPageChart ��Ϣ�������


BOOL CPageChart::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
