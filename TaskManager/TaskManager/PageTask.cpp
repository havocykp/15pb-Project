// PageTask.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TaskManager.h"
#include "PageTask.h"
#include "afxdialogex.h"


// CPageTask �Ի���
HWND hwnd;

IMPLEMENT_DYNAMIC(CPageTask, CDialogEx)

CPageTask::CPageTask(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PAGE_TASK, pParent)
{

}

CPageTask::~CPageTask()
{
}

void CPageTask::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_TASK, m_Task);
}


BEGIN_MESSAGE_MAP(CPageTask, CDialogEx)
END_MESSAGE_MAP()


// CPageTask ��Ϣ�������

// Ӧ�ó���
BOOL CPageTask::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��



	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
