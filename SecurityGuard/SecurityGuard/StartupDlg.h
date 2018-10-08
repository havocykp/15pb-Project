#pragma once
#include "StartupList.h"
#include <vector>

typedef struct _SOFTINFO1
{
	WCHAR szSoftName[50];			        //�������
	WCHAR szSoftVer[50];				    //����汾��
	WCHAR szSoftDate[20];				    //�����װ����
	WCHAR szSoftSize[MAX_PATH];				//�����С
	WCHAR strSoftInsPath[MAX_PATH];			//�����װ·��
	WCHAR strSoftUniPath[MAX_PATH];			//���ж��·��
	WCHAR strsoftVenRel[50];				//�����������
	WCHAR strSoftIco[MAX_PATH];				//���ͼ��·��
	WCHAR szSoftPub[50];

}SOFTINFO1, *PSOFTINFO1;

// CStartupDlg �Ի���

class CStartupDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStartupDlg)

public:
	CStartupDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CStartupDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_StartUp };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	//void UpdateStartupInfo();
	HKEY m_hRootKey;					  //����
	CString m_SubKey1;					  //�Ӽ�1
	CString m_SubKey2;					  //�Ӽ�2

	CString m_KeyName;					  //����
	CString m_KeyNameVer;				  //�汾
	CString m_KeyNameDate;				  //����
	CString m_KeyNameSize;				  //��С
	CString m_KeyNamePub;				  //����
	CString m_KeyNameInsPath;			  //��װ·��
	CString m_KeyNameUniPath;			  //ж��·��

	CString m_SoftName;					  //��ʾ����
	CString m_SoftPub;					  //����
	CString m_SoftDate;					  //����
	CString m_SoftSize;					  //�ߴ�
	CString m_SoftVer;					  //�汾
	CString m_SoftInsPath;				  //��װ·��
	CString m_SoftUniPath;				  //ж��·��

	std::vector<SOFTINFO1> m_vecSoftInfo;	//�洢��Ϣ
	void GetSoftwareInfo(CString SubKey);	//��ȡ�����Ϣ	

public:

	CStartupList m_StartupList;
	afx_msg void OnUnload(); // ж��
	afx_msg void OnBrush(); // ˢ��
	afx_msg void OnOpenfile(); // ����
	afx_msg void OnNMRClickListStartup(NMHDR *pNMHDR, LRESULT *pResult);
};
