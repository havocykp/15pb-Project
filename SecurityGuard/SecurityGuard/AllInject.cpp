// AllInject.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SecurityGuard.h"
#include "AllInject.h"
#include "afxdialogex.h"


// CAllInject �Ի���

IMPLEMENT_DYNAMIC(CAllInject, CDialogEx)

CAllInject::CAllInject(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_Inject, pParent)
{

}

CAllInject::~CAllInject()
{
}

void CAllInject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAllInject, CDialogEx)
END_MESSAGE_MAP()


// CAllInject ��Ϣ�������
