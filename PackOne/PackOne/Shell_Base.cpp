#include "stdafx.h"
#include "Shell_Base.h"


CShell_Base::CShell_Base()
{
	memset(&m_PEinMem, 0, sizeof(PESTC));
}


CShell_Base::~CShell_Base()
{
	if (m_PEinMem.pDosHead)
	{
		char* pFile = (char*)m_PEinMem.pDosHead;
		delete[] pFile;
	}
	if (m_PEinMem.hStub)
	{
		FreeLibrary(m_PEinMem.hStub);
	}
}

/*1.����NTͷָ��,2.RVAֵ*/
/*ת��ʧ�ܷ���0*/
DWORD CShell_Base::RVA2Offset(PIMAGE_NT_HEADERS32 pNtHead, DWORD dwAddr)
{
	/*VA=RVA+��ַ(Image Base)*/
	/*���ƫ��=Ŀ���FOA-Ŀ�����ڶε���ʼλ��FOA*/
	/*���ƫ��=Ŀ���RVA-Ŀ�����ڶε���ʼλ��RVA*/

	WORD wCount = pNtHead->FileHeader.NumberOfSections;
	PIMAGE_SECTION_HEADER pCurSec = IMAGE_FIRST_SECTION(pNtHead);//��һ������ͷ


	//��ͷ��ֱ�ӷ���
	if (dwAddr < pNtHead->OptionalHeader.SizeOfHeaders)
	{
		return dwAddr;
	}

	//�ҵ�RVA�����ĸ��ڴ����ĸ�������
	for (WORD i = 0; i < wCount; i++)
	{
		if (dwAddr < (pCurSec->VirtualAddress + pCurSec->SizeOfRawData) &&
			dwAddr >= pCurSec->VirtualAddress)
		{
			//FOA = RVA - �ڴ������ε���ʼλ�� + ���ļ������ε���ʼλ�� 
			return dwAddr - pCurSec->VirtualAddress + pCurSec->PointerToRawData;
		}
		//�¸�����
		pCurSec++;
	}


	return 0;
}

//��λpPE(�ڴ�)�е�PE�ṹ;
void CShell_Base::PositionPE(char* pPE, PPESTC pPEstc)
{
	pPEstc->pDosHead = (PIMAGE_DOS_HEADER)pPE;
	pPEstc->pNtHead = (PIMAGE_NT_HEADERS)(pPEstc->pDosHead->e_lfanew + pPE);
	pPEstc->pFirstSectionHead = IMAGE_FIRST_SECTION(pPEstc->pNtHead);
	pPEstc->pLastSectionHead =
		pPEstc->pFirstSectionHead + (m_PEinMem.pNtHead->FileHeader.NumberOfSections - 1);
}


/*����RawSize��AlignmentΪ�������ж���Ĵ�С*/
inline DWORD CShell_Base::Alignment(DWORD dwRawSize, DWORD dwAlignment)
{
	if (dwRawSize%dwAlignment == 0)
	{
		return dwRawSize;
	}
	else
	{
		return (dwRawSize / dwAlignment + 1)*dwAlignment;
	}
}

/*��m_NewPE�����λ����ϼ�һ������*/
/*1.���ε����� 2.�������ݵĴ�С 3.�������� 4.���ε�����*/
void CShell_Base::AddSection(char* pNewSection, DWORD dwNewSectionLen,
	char * szNewSectionName, DWORD dwNewSectionAttribute)
{

	DWORD dwOriginFileSize = m_PEinMem.dwFileSize;
	//1 ����һ���µĿռ䣬�������������κ��PE�ļ�
	m_PEinMem.dwFileSize = m_PEinMem.dwFileSize +
		Alignment(dwNewSectionLen, m_PEinMem.pNtHead->OptionalHeader.FileAlignment);

	char* pTmp = new char[m_PEinMem.dwFileSize];

	memset(pTmp, 0, m_PEinMem.dwFileSize);

	//��ԭPE�ļ����������ڴ���.
	memcpy(pTmp, (char*)m_PEinMem.pDosHead, dwOriginFileSize);


	//�ͷ�ԭ��ռ�õ���Դ
	char* pFileBuf = (char*)m_PEinMem.pDosHead;
	delete[] pFileBuf;

	//��λ���ڴ��е�PE�ṹ;
	PositionPE(pTmp, &m_PEinMem);


	//2 ��ʼ���������
	//2.1 �޸�ͷ����Ϣ�����������α�PEͷ�е�������������չͷ�е�SizeOfImage
	//2.2 �ҵ����α�����һ��
	PIMAGE_SECTION_HEADER pOriginLastSection =
		m_PEinMem.pFirstSectionHead + (m_PEinMem.pNtHead->FileHeader.NumberOfSections - 1);

	PIMAGE_SECTION_HEADER pNewLastSection =
		m_PEinMem.pFirstSectionHead + m_PEinMem.pNtHead->FileHeader.NumberOfSections;

	//3 ��ʼ������α���Ϣ
	strcpy_s((char *)pNewLastSection->Name, 8, szNewSectionName);//������

	pNewLastSection->Characteristics = dwNewSectionAttribute;//��������

	//���ε��ļ�ƫ��
	pNewLastSection->PointerToRawData = pOriginLastSection->PointerToRawData +
		pOriginLastSection->SizeOfRawData;

	//�������ļ��еĴ�С
	pNewLastSection->SizeOfRawData =
		Alignment(dwNewSectionLen, m_PEinMem.pNtHead->OptionalHeader.FileAlignment);

	//������ʼλ�õ�RVA
	pNewLastSection->VirtualAddress = pOriginLastSection->VirtualAddress +
		Alignment(pOriginLastSection->Misc.VirtualSize, m_PEinMem.pNtHead->OptionalHeader.SectionAlignment);

	pNewLastSection->Misc.VirtualSize = dwNewSectionLen;//δ��������ݴ�С

	m_PEinMem.pNtHead->FileHeader.NumberOfSections++;//����������Ŀ

	//���ص��ڴ���������ڴ��С����������룩
	m_PEinMem.pNtHead->OptionalHeader.SizeOfImage = m_PEinMem.pNtHead->OptionalHeader.SizeOfImage +
		Alignment(dwNewSectionLen, m_PEinMem.pNtHead->OptionalHeader.SectionAlignment);

	//4.��PE�ļ��ĺ������һ��������
	memcpy((char*)((DWORD)m_PEinMem.pDosHead + pNewLastSection->PointerToRawData), pNewSection, dwNewSectionLen);

	//���¶�λ���ڴ��е�PE�ṹ;
	PositionPE(pTmp, &m_PEinMem);
}

void CShell_Base::LoadStubDll()
{
	m_PEinMem.hStub = LoadLibrary(L"Stub.dll");
	m_PEinMem.pStubInfo = (PGLOBAL_PARAM)GetProcAddress(m_PEinMem.hStub, "g_StubInfo");
}

void CShell_Base::AddStub()
{
	//1.�õ�ԭ�����OEP�����õ�pStubInfo��
	m_PEinMem.pStubInfo->dwOriginOEP_RVA = m_PEinMem.pNtHead->OptionalHeader.AddressOfEntryPoint;

	//2.��λhStub��PE�ṹ
	PIMAGE_DOS_HEADER pDosHead = (PIMAGE_DOS_HEADER)m_PEinMem.hStub;
	PIMAGE_NT_HEADERS pNtHead = (PIMAGE_NT_HEADERS)(pDosHead->e_lfanew + (LONG)m_PEinMem.hStub);
	PIMAGE_SECTION_HEADER pFirstSection = IMAGE_FIRST_SECTION(pNtHead);

	DWORD dwOEPinDll_RVA = pNtHead->OptionalHeader.AddressOfEntryPoint;


	//�������ݵ�Stub
	m_PEinMem.pStubInfo->dwIAT_RVA =
		m_PEinMem.pNtHead->OptionalHeader.DataDirectory[1].VirtualAddress;

	//���θ�Stub
	m_PEinMem.pStubInfo->dwOrignalImageBase = m_PEinMem.pNtHead->OptionalHeader.ImageBase;

	//��ԭ�ض�λ��RVAͬ����Stub��
	m_PEinMem.pStubInfo->dwReloc_RVA =
		m_PEinMem.pNtHead->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress;

	//�����������
	m_PEinMem.pStubInfo->dwStart_RVA = m_PEinMem.pFirstSectionHead->VirtualAddress;

	DWORD dwRawSize = m_PEinMem.pFirstSectionHead->Misc.VirtualSize;

	m_PEinMem.pStubInfo->dwEnd_RVA =
		m_PEinMem.pFirstSectionHead->VirtualAddress + dwRawSize - (dwRawSize % 4);

	m_PEinMem.pStubInfo->dwEnd_RVA -= 4;

	//ȡStub���д�������
	DWORD dwStubOEPRVA = m_PEinMem.pStubInfo->dwStubOEP_RVA - (DWORD)m_PEinMem.hStub;

	DWORD dwStubOEPOffsetInSection = dwStubOEPRVA - pNtHead->OptionalHeader.BaseOfCode;

	FixStubRelocInDLL();

	AddSection((char*)(pFirstSection->VirtualAddress + (DWORD)m_PEinMem.hStub),
		pFirstSection->Misc.VirtualSize, ".Stub", pFirstSection->Characteristics);

	//���ɻ���exe����OEP
	DWORD dwNewOEP = dwStubOEPOffsetInSection + m_PEinMem.pLastSectionHead->VirtualAddress;

	char* pRelocBuf = NULL;
	DWORD dwBufSize = 0;
	DWORD dwRelocSectionCharacter = 0;
	FixStubRelocBlock(&pRelocBuf, &dwBufSize, &dwRelocSectionCharacter);
	// ��Ŀ����򹹽�һ���ض�λ��
	AddSection(pRelocBuf, dwBufSize, ".Reloc", dwRelocSectionCharacter);

	//�ͷŴ洢.Rreloc����Դ
	delete[] pRelocBuf;
	pRelocBuf = NULL;
	//���ض�λ��ָ��Stub���ض�λ��
	m_PEinMem.pNtHead->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress
		= m_PEinMem.pLastSectionHead->VirtualAddress;

	m_PEinMem.pNtHead->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].Size = dwBufSize;


	//����������Ϣ
	m_PEinMem.pNtHead->OptionalHeader.DataDirectory[1].Size = 0;

	m_PEinMem.pNtHead->OptionalHeader.DataDirectory[1].VirtualAddress = 0;


	//���IAT
	m_PEinMem.pNtHead->OptionalHeader.DataDirectory[12].Size = 0;

	m_PEinMem.pNtHead->OptionalHeader.DataDirectory[12].VirtualAddress = 0;


	//����Ŀ������OEP����������
	m_PEinMem.pNtHead->OptionalHeader.AddressOfEntryPoint = dwNewOEP;

	//ȥ�������ַ
	//m_PEinMem.pNtHead->OptionalHeader.DllCharacteristics &= ~IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE;
}

void CShell_Base::FixStubRelocInDLL()
{
	//��λDll��PE��Ϣ
	PIMAGE_DOS_HEADER pDosHead = (PIMAGE_DOS_HEADER)m_PEinMem.hStub;
	PIMAGE_NT_HEADERS pNtHead = (PIMAGE_NT_HEADERS)(pDosHead->e_lfanew + (LONG)m_PEinMem.hStub);
	PIMAGE_SECTION_HEADER pFirstSection = IMAGE_FIRST_SECTION(pNtHead);

	//�޸��ض�λ��Ϣ
	PIMAGE_DATA_DIRECTORY pRelocDir = pNtHead->OptionalHeader.DataDirectory + 5;
	PIMAGE_BASE_RELOCATION pRelocBlock = (PIMAGE_BASE_RELOCATION)(pRelocDir->VirtualAddress + (DWORD)m_PEinMem.hStub);

	DWORD dwNewSectionRVA = m_PEinMem.pLastSectionHead->VirtualAddress +
		Alignment(m_PEinMem.pLastSectionHead->SizeOfRawData, m_PEinMem.pNtHead->OptionalHeader.SectionAlignment);

	//�����λ�ַ-ԭ���λ�ַ=���β�ֵ
	DWORD dwDifference = (dwNewSectionRVA - pNtHead->OptionalHeader.BaseOfCode);



	while (pRelocBlock->SizeOfBlock != 0 && pRelocBlock->VirtualAddress >= pFirstSection->VirtualAddress
		&& pRelocBlock->VirtualAddress < (pFirstSection->VirtualAddress + pFirstSection->Misc.VirtualSize))
	{
		DWORD dwCount = (pRelocBlock->SizeOfBlock - 8) / sizeof(WORD);
		PTYPEOFFSET pTypeOffset = (PTYPEOFFSET)(pRelocBlock + 1);
		for (DWORD i = 0; i < dwCount; i++)
		{
			if (pTypeOffset[i].Type == 3)
			{
				DWORD dwRVA = pTypeOffset[i].Offset + pRelocBlock->VirtualAddress;


				// �޸��ض�λ��Ϣ   ��ʽ����Ҫ�޸��ĵ�ַ-ԭӳ���ַ-ԭ���λ�ַ+�����λ�ַ+��ӳ���ַ
				//FAR��ַ��LordPE��������ע��
				DWORD AddrOfNeedReloc = *(DWORD*)((DWORD)pDosHead + dwRVA);

				DWORD dwRelocItemRVA = AddrOfNeedReloc - pNtHead->OptionalHeader.ImageBase;

				DWORD dwRelocItemVAinNewPE = dwRelocItemRVA + m_PEinMem.pNtHead->OptionalHeader.ImageBase;

				*(DWORD*)((DWORD)pDosHead + dwRVA) = (dwRelocItemVAinNewPE + dwDifference);

			}

		}
		pRelocBlock = (PIMAGE_BASE_RELOCATION)((char *)pRelocBlock + pRelocBlock->SizeOfBlock);
	}
}


/*����޸��ض�λ����ض�λ��Buf,�������Buf�Ĵ�С�����ε�����*/
void CShell_Base::FixStubRelocBlock(char** ppRelocTableBuf, DWORD* lpBufLenth, DWORD* lpSectionCharacter)
{
	//��λDll��PE��Ϣ
	PIMAGE_DOS_HEADER pDosHead = (PIMAGE_DOS_HEADER)m_PEinMem.hStub;
	PIMAGE_NT_HEADERS pNtHead = (PIMAGE_NT_HEADERS)(pDosHead->e_lfanew + (LONG)m_PEinMem.hStub);
	PIMAGE_SECTION_HEADER pFirstSection = IMAGE_FIRST_SECTION(pNtHead);

	//�޸��ض�λ��Ϣ
	PIMAGE_DATA_DIRECTORY pRelocDir = pNtHead->OptionalHeader.DataDirectory + 5;
	PIMAGE_BASE_RELOCATION pRelocBlock = (PIMAGE_BASE_RELOCATION)(pRelocDir->VirtualAddress + (DWORD)m_PEinMem.hStub);
	DWORD dwTotalBlockSize = 0;

	PIMAGE_SECTION_HEADER pLastSection = pFirstSection + (pNtHead->FileHeader.NumberOfSections - 1);

	//ȡDLL���һ���ε�����
	*lpSectionCharacter = pLastSection->Characteristics;

	//ֻ�޸�dll��ָ���һ�����ε��ض�λ��
	while (pRelocBlock->SizeOfBlock != 0 && pRelocBlock->VirtualAddress >= pFirstSection->VirtualAddress
		&& pRelocBlock->VirtualAddress < (pFirstSection->VirtualAddress + pFirstSection->Misc.VirtualSize))
	{

		//ͳ��Ҫ�޸�Ҫ���ƶ����ض�λ��
		dwTotalBlockSize += pRelocBlock->SizeOfBlock;

		DWORD dwOldProtect;

		VirtualProtect(pRelocBlock, 1, PAGE_EXECUTE_READWRITE, &dwOldProtect);

		//���ض�λ��RVA�޸���������EXE��RVA���ض�λ�����������Σ�Stub�����ڵ����ڶ������Σ�

		DWORD* pNeed2Fix = (DWORD*)pRelocBlock;

		*pNeed2Fix = (pRelocBlock->VirtualAddress - pFirstSection->VirtualAddress + m_PEinMem.pLastSectionHead->VirtualAddress);

		VirtualProtect(pRelocBlock, 1, dwOldProtect, &dwOldProtect);

		//��һ���ض�λ��
		pRelocBlock = (PIMAGE_BASE_RELOCATION)((char*)pRelocBlock + pRelocBlock->SizeOfBlock);
	}

	*ppRelocTableBuf = new char[dwTotalBlockSize + 8];

	memset(*ppRelocTableBuf, 0, dwTotalBlockSize + 8);

	memcpy(*ppRelocTableBuf, (char*)(pRelocDir->VirtualAddress + (DWORD)m_PEinMem.hStub), dwTotalBlockSize);

	*lpBufLenth = dwTotalBlockSize + 8;


}

void CShell_Base::Encode(DWORD dwHash)
{
	DWORD dwImageBase = (DWORD)m_PEinMem.pDosHead;
	DWORD dwBegin = RVA2Offset(m_PEinMem.pNtHead, m_PEinMem.pStubInfo->dwStart_RVA) + dwImageBase;
	DWORD dwEnd = RVA2Offset(m_PEinMem.pNtHead, m_PEinMem.pStubInfo->dwEnd_RVA) + dwImageBase;

	PDWORD pdwBegin = (PDWORD)dwBegin;
	PDWORD pdwEnd = (PDWORD)dwEnd;

	while (pdwBegin != pdwEnd)
	{
		(*pdwBegin) ^= dwHash;
		pdwBegin++;
	}

}

DWORD CShell_Base::HashPassWord(char * Src)
{
	DWORD dwRet = 0;

	while (*Src)
	{
		dwRet = ((dwRet << 25) | (dwRet >> 7));
		dwRet = dwRet + *Src;
		Src++;
	}

	return dwRet;
}


void CShell_Base::ReleaseAll()
{
	if (m_PEinMem.pDosHead)
	{
		char* pBuf = (char*)m_PEinMem.pDosHead;
		delete[]pBuf;
		m_PEinMem.pDosHead = NULL;
		m_PEinMem.pNtHead = NULL;
		m_PEinMem.dwFileSize = NULL;
		m_PEinMem.pFirstSectionHead = NULL;
		m_PEinMem.pLastSectionHead = NULL;
	}

	if (m_PEinMem.hStub)
	{
		FreeLibrary(m_PEinMem.hStub);
		m_PEinMem.hStub = NULL;
		m_PEinMem.pStubInfo = NULL;
	}
}

/*�����ļ�·�������ļ������ڴ���*/
/*������ΪWin32PE�򷵻�true����������m_OriginPE*/
bool CShell_Base::LoadFile(TCHAR *szFilePath)
{
	HANDLE hFile = CreateFile(szFilePath, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	DWORD dwFileSize = GetFileSize(hFile, NULL);
	char* pFileBuf = new char[dwFileSize];
	DWORD dwRead = 0;

	//��ȡ�ļ�������ԭȫ������
	if (!ReadFile(hFile, pFileBuf, dwFileSize, &dwRead, NULL) || dwFileSize != dwRead)
	{
		delete[] pFileBuf;
		pFileBuf = NULL;
		CloseHandle(hFile);
		return false;
	}

	PIMAGE_DOS_HEADER pDosHead = (PIMAGE_DOS_HEADER)pFileBuf;
	PIMAGE_NT_HEADERS32 pNtHead =
		(PIMAGE_NT_HEADERS32)((LONG)pFileBuf + pDosHead->e_lfanew);


	if (pDosHead->e_magic != IMAGE_DOS_SIGNATURE ||
		pNtHead->OptionalHeader.Magic != 0x10B ||
		pNtHead->Signature != IMAGE_NT_SIGNATURE)	//DOSͷ��ǲ���5A4D��NTͷ��ǲ���4550,PE����Win32��
	{
		delete[] pFileBuf;
		pFileBuf = NULL;
		CloseHandle(hFile);
		return false;
	}

	m_PEinMem.dwFileSize = dwFileSize;
	PositionPE(pFileBuf, &m_PEinMem);

	CloseHandle(hFile);
	return true;
}

/*�����ļ�·�������ڴ�д���ļ��У������򷵻�true*/
bool CShell_Base::SaveFile(TCHAR * szFilePath)
{
	HANDLE hFile = CreateFile(szFilePath, GENERIC_WRITE, NULL,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	DWORD dwWrite = 0;

	//��ȡ�ļ������رվ��
	if (!WriteFile(hFile, m_PEinMem.pDosHead, m_PEinMem.dwFileSize, &dwWrite, NULL) ||
		m_PEinMem.dwFileSize != dwWrite)
	{
		CloseHandle(hFile);
		return false;
	}

	CloseHandle(hFile);
	return true;
}

