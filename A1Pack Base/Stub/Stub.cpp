// Stub.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "Stub.h"

extern __declspec(dllexport) GLOBAL_PARAM g_stcParam = { 0 };
LPGETPROCADDRESS g_funGetProcAddress = nullptr;
LPLOADLIBRARYEX g_funLoadLibraryEx = nullptr;

LPEXITPROCESS g_funExitProcess = nullptr;
LPMESSAGEBOX g_funMessageBox = nullptr;
LPGETMODULEHANDLE g_funGetModuleHandle = nullptr;
LPVIRTUALPROTECT g_funVirtualProtect = nullptr;

// ��ȡKernel32.dll��ģ���ַ
DWORD GetKernel32Base()
{
	OutputDebugString(L"GetKernel32Base Function Entry!");
	DWORD dwKernel32Addr = 0;
	__asm
	{
		push eax
		mov eax,dword ptr fs:[0x30] // PEB�ĵ�ַ
		mov eax,[eax+0x0C] // ָ��PEB_LDR_DATA�ṹ��ָ��
		mov eax,[eax+0x1C] // ģ���ʼ�������ͷָ��InInitializationOrderModuleList
		mov eax,[eax] // �б��еĵڶ�����Ŀ
		mov eax,[eax+0x08] // ��ȡ����Kernel32.dll��ַ
		mov dwKernel32Addr,eax
		pop eax
	}

	return dwKernel32Addr;
}

// ��ȡGetProcAddress�ĺ�����ַ
DWORD GetGPAFunAddr()
{
	OutputDebugString(L"GetGPAFunAddr Function Entry!");
	DWORD dwAddrBase = GetKernel32Base();

	// 1. ��ȡDOSͷ��NTͷ
	PIMAGE_DOS_HEADER pDos_Header;
	PIMAGE_NT_HEADERS pNt_Header;
	pDos_Header = (PIMAGE_DOS_HEADER)dwAddrBase;
	pNt_Header = (PIMAGE_NT_HEADERS)(dwAddrBase + pDos_Header->e_lfanew);

	// 2. ��ȡ��������
	PIMAGE_DATA_DIRECTORY pDataDir;
	PIMAGE_EXPORT_DIRECTORY pExport;
	pDataDir = pNt_Header->OptionalHeader.DataDirectory + IMAGE_DIRECTORY_ENTRY_EXPORT;

	// 3. ��ȡ��������ϸ��Ϣ
	PDWORD pAddrOfFun = (PDWORD)(pExport->AddressOfFunctions + dwAddrBase);
	PDWORD pAddrOfNames = (PDWORD)(pExport->AddressOfNames + dwAddrBase);
	PDWORD pAddrOfOrdinals = (PDWORD)(pExport->AddressOfNameOrdinals + dwAddrBase);

	// 4. �����Ժ��������Һ�����ַ������ѭ����ȡENT�еĺ����������봫��ֵ�Աȶԣ�����ƥ����
	//	  ����EAT����ָ�������Ϊ��������ȡ�����ֵַ
	DWORD dwFunAddr;
	for (DWORD i = 0; i < pExport->NumberOfNames; i++)
	{
		PCHAR lpFunName = (PCHAR)(pAddrOfNames[i] + dwAddrBase);
		if (!strcmp(lpFunName, "GetProcAddress"))
		{
			dwFunAddr = pAddrOfFun[pAddrOfOrdinals[i]] + dwAddrBase;
			break;
		}
		if (i == pExport->NumberOfNames - 1)
			return 0;
	}

	return dwFunAddr;
}

// ��ʼ��API
bool InitializationAPI()
{
	OutputDebugString(L"InitializationAPI Function Entry!");
	HMODULE hModule;

	// 1. ��ʼ������API
	g_funGetProcAddress = (LPGETPROCADDRESS)GetGPAFunAddr();
	g_funLoadLibraryEx = (LPLOADLIBRARYEX)g_funGetProcAddress((HMODULE)GetKernel32Base(), "LoadLibraryExW");

	// 2. ��ʼ������API
	hModule = NULL;
	if (!(hModule = g_funLoadLibraryEx(L"kernel32.dll", NULL, NULL))) return false;
	g_funExitProcess = (LPEXITPROCESS)g_funGetProcAddress(hModule, "ExitProcess");
	hModule = NULL;
	if (!(hModule = g_funLoadLibraryEx(L"user32.dll", NULL, NULL))) return false;
	g_funMessageBox = (LPMESSAGEBOX)g_funGetProcAddress(hModule, "MessageBoxW");
	hModule = NULL;
	if (!(hModule = g_funLoadLibraryEx(L"kernel32.dll", NULL, NULL))) return false;
	g_funGetModuleHandle = (LPGETMODULEHANDLE)g_funGetProcAddress(hModule, "GetModuleHandleW");
	hModule = NULL;
	if (!(hModule = g_funLoadLibraryEx(L"kernel32.dll", NULL, NULL))) return false;
	g_funVirtualProtect = (LPVIRTUALPROTECT)g_funGetProcAddress(hModule, "VirtualProtect");

	return true;
}

// ���ܺ���
void Decrypt()
{
	OutputDebugString(L"Decrypt Function Entry!");
	// �ڵ�����ȫ�ֱ����ж�ȡ��Ҫ�����������ʼ�ڽ���VA
	PBYTE lpStart = g_stcParam.lpStartVA;
	PBYTE lpEnd = g_stcParam.lpEndVA;

	// ѭ������
	while (lpStart < lpEnd)
	{
		*lpStart -= 0x88;
		*lpStart ^= 0xA1;
		lpStart++;
	}
}

