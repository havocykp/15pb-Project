#include<Windows.h>
#include<iostream>

using namespace std;

int main()
{
	HANDLE hToken;
	bool flag = OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);
	cout << "�������㱻�ٳ���!" << endl;
	cin.get();
}