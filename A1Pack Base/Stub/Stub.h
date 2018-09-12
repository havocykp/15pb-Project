#pragma once
#include <windows.h>

// ����һ��������ȫ�ֱ��������Ա��洫�ݸ�Stub���ֵĲ���
typedef struct _GLOBAL_PARAM
{
	BOOL bShowMessage; // �Ƿ���ʾ������Ϣ
	DWORD dwOEP; // ������ڵ�
	PBYTE lpStartVA; // ��ʼ�����ַ��������������
	PBYTE lpEndVA; // ���������ַ��������������
}GLOBAL_PARAM, *PGLOBAL_PARAM;
extern "C" __declspec(dllexport) GLOBAL_PARAM g_stcParam;

// ����API��������
typedef DWORD(WINAPI *LPGETPROCADDRESS)(HMODULE, LPCSTR); // GetProcAddress
typedef HMODULE(WINAPI *LPLOADLIBRARYEX)(LPCTSTR, HANDLE, DWORD); // LoadLibraryEx
extern LPGETPROCADDRESS g_funGetProcAddress;
extern LPLOADLIBRARYEX g_funLoadLibraryEx;

// ����API��������
typedef VOID(WINAPI *LPEXITPROCESS)(UINT); // ExitProcess
typedef int (WINAPI *LPMESSAGEBOX)(HWND, LPCTSTR, LPCTSTR, UINT); // MessageBOx
typedef HMODULE(WINAPI *LPGETMODULEHANDLE)(LPCWSTR); // GetModuleHandle
typedef BOOL(WINAPI *LPVIRTUALPROTECT)(LPVOID, SIZE_T, DWORD, PDWORD); // VirtualProtect
extern LPEXITPROCESS g_funExitProcess;
extern LPMESSAGEBOX g_funMessageBox;
extern LPGETMODULEHANDLE g_funGetModuleHandle;
extern LPVIRTUALPROTECT g_funVirtualProtect;

// �������ܺ���
extern DWORD GetKernel32Base(); // ��ȡKernel32.dll��ģ���ַ
extern DWORD GetGPAFunAddr(); // ��ȡGetProcAddress�ĺ�����ַ
extern bool InitializationAPI(); // ��ʼ������API
extern void Decrypt(); // ���ܺ���