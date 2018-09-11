#pragma once
#include <windows.h>

typedef struct _GLOBAL_PARAM
{
	DWORD dwStubOEP_RVA;	//�ǳ������ڵ�
	DWORD dwOriginOEP_RVA;   //���ӿǵĳ���ԭʼ��ڵ�

	DWORD dwStart_RVA;	// ��ʼ�����ַ�����������������ڴ��У�
	DWORD dwEnd_RVA;      // ���������ַ�����������������ڴ��У�

	DWORD dwOrignalImageBase;//���ӿǵĳ����ԭʼ�����ַ

	DWORD dwIAT_RVA; //�ӿǵĵ�����ַ
	DWORD dwTLS_Size; //�ӿǵ�tls���ݴ�С
	DWORD dwTLS_RVA; //�ӿǵ�tls�����ַ rva
	DWORD dwReloc_RVA; //�ض�λrva

}GLOBAL_PARAM, *PGLOBAL_PARAM;

typedef struct _PESTC
{
	PIMAGE_DOS_HEADER pDosHead;
	PIMAGE_NT_HEADERS pNtHead;
	PIMAGE_SECTION_HEADER pFirstSectionHead;
	PIMAGE_SECTION_HEADER pLastSectionHead;
	HMODULE hStub;
	PGLOBAL_PARAM pStubInfo;
	DWORD dwFileSize;
}PESTC, *PPESTC;


typedef struct _TYPEOFFSET
{
	WORD Offset : 12; //��12λ������ض�λ���ƫ��
	WORD Type : 4;
}TYPEOFFSET, *PTYPEOFFSET;


class CShell_Base
{
public:
	CShell_Base();
	~CShell_Base();

public:
	DWORD RVA2Offset(PIMAGE_NT_HEADERS32 pNtHead, DWORD dwAddr);

	bool LoadFile(TCHAR * szFilePath);
	bool SaveFile(TCHAR * szFilePath);

	void PositionPE(char* pPE, PPESTC pPEstc);
	inline DWORD Alignment(DWORD dwRawSize, DWORD dwAlignment);
	void AddSection(char* pNewSection, DWORD dwNewSectionLen, char * szNewSectionName, DWORD dwNewSectionAttribute);
	void LoadStubDll();
	void AddStub();
	void FixStubRelocInDLL();
	void FixStubRelocBlock(char** ppRelocTableBuf, DWORD* lpBufLenth, DWORD* lpSectionCharacter);
	void Encode(DWORD dwHash);
	DWORD HashPassWord(char * Src);
	void ReleaseAll();


protected:
	PESTC m_PEinMem;
};

