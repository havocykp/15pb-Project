// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "Stub.h"

#pragma comment(linker, "/entry:\"StubEntryPoint\"") // ָ��������ں���ΪStubEntryPoint()
#pragma comment(linker, "/merge:.data=.text") // ��.data�ϲ���.text
#pragma comment(linker, "/merge:.rdata=.text") // ��.rdata�ϲ���.text
#pragma comment(linker, "/section:.text,RWE") // ��.text�ε���������Ϊ�ɶ�����д����ִ��

// Stub��ʼ����
void start()
{
	// 1. ��ʼ������API
	if (!InitializationAPI()) return;

	// 2. ������������
	Decrypt();

	// 3. ѯ���Ƿ�ִ�н��ܺ�ĳ���
	if (g_stcParam.bShowMessage)
	{
		int nRet = g_funMessageBox(NULL, L"������ɣ��Ƿ�����ԭ����", L"�������", MB_OKCANCEL);
		if (IDCANCEL == nRet) return;
	}

	// 4. ��ת��OEP
	__asm jmp g_stcParam.dwOEP;
}

// Stub���ֵ���ں���
void __declspec(naked) StubEntryPoint()
{
	__asm sub esp, 0x50; // ̧��ջ������߼�����
	start(); // ִ�пǵ����岿��
	__asm add esp, 0x50; // ƽ���ջ

	// ��������ExitProcess�����˳����̿��Խ��һЩ����������
	if (g_funExitProcess)
	{
		g_funExitProcess(0);
	}

	__asm retn;
}


