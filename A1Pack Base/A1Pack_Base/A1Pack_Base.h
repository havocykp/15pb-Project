#pragma once
#include "resource.h"
#include "ProcessingPE.h"
#include <stdlib.h>
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#ifdef A1PACK_BASE_EXPORTS
#define A1PACK_BASE_API __declspec(dllexport)
#else
#define A1PACK_BASE_API __declspec(dllimport)
#endif // A1PACK_BASE_EXPORTS

// ���Ա��洫�ݸ�Stub���ֵĲ���
typedef struct _GLOBAL_PARAM
{
	BOOL bShowMessage; // �Ƿ���ʾ������Ϣ
	DWORD dwOEP; // ������ڵ�
	PBYTE lpStartVA; // ��ʼ�����ַ (����������)
	PBYTE lpEndVA; // ���������ַ (����������)
}GLOBAL_PARAM, *PGLOBAL_PARAM;

// ����һ��������API��������������ִ�мӿǲ���
A1PACK_BASE_API bool A1Pack_Base(LPWSTR strPath, bool bShowMsg);

// �ӿ�ʱ���õ��ĺ�������
extern void Pretreatment(PBYTE lpCodeStart, PBYTE lpCodeEnd, PE_INFO stcPeInfo); // Ԥ������
extern DWORD Implantation(LPVOID &lpFileData, DWORD dwSize, CProcessingPE* pobjPE, PE_INFO stcPeInfo, GLOBAL_PARAM stcParam); // Stubֲ�뺯��
