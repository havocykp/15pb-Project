#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "control.h"
#include "interface.h"
#include <windows.h>


/**
* ������
*/
int main()
{
	system("mode con cols=100 lines=30");   //���ÿ���̨�Ŀ��
	system("title Snake online"); 

	printsnake();
	welcometogame();
	File_out();
	keyboardControl();
	endgame();



	return 0;
}