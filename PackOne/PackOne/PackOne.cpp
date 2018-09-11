// PackOne.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Shell_Base.h"
#include <iostream>

using namespace std;

int main()
{
	CShell_Base obj;
	TCHAR szPath[MAX_PATH];

	memset(szPath, 0, MAX_PATH);
	cout << "\n������Ҫ�ӿǵĳ����·�� > ";
	wscanf_s(L"%s", szPath, MAX_PATH - 2);
	if (!obj.LoadFile(szPath))
	{
		cout << "�޷������ļ������򼴽��˳�!\n";
		system("pause");
	}

	obj.LoadStubDll();

	cout << "\n������Ҫ����ļ������� > ";
	char szPSW[512];
	if (1 != scanf_s("%s", szPSW, MAX_PATH - 2))
	{
		cout << "��������Ч�����򼴽��˳�!\n";
		system("pause");
		obj.ReleaseAll();
	}
	DWORD dwHash = obj.HashPassWord(szPSW);
	if (dwHash == 0)
	{
		cout << "��������Ч�����򼴽��˳�!\n";
		system("pause");
		obj.ReleaseAll();
	}

	obj.AddStub();

	obj.Encode(dwHash);

	cout << "\n������Ҫ��������·�� > ";
	memset(szPath, 0, MAX_PATH);
	wscanf_s(L"%s", szPath, MAX_PATH - 2);
	if (!obj.SaveFile(szPath))
	{
		cout << "�޷������ļ������򼴽��˳�!\n";
		system("pause");
		obj.ReleaseAll();
	}

	cout << "\n�ӿǳɹ������򼴽��˳���\n";
	obj.ReleaseAll();

	system("pause");
    return 0;
}

