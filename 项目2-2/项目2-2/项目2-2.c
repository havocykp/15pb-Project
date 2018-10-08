// ��Ŀ2-2.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <time.h>
#include <math.h>
#include <conio.h>

//����ȫ�ֱ���
int step = 0; //��ִ�в���
int score = 0; //�洢��Ϸ����
long int Time; //��Ϸ����ʱ��
int BOX[4][4] = { 0,0,0,0,//��Ϸ�е�16������
				  0,0,0,0,
				  0,0,0,0,
				  0,0,0,0 };
HANDLE hOut; //����̨���


//��������
void setPos(int x, int y);//��ȡ��Ļ���λ��					  
int color(int c);//������ɫ����	 
int textColor(int number);//���������޸���ɫ				  
void drawTheGameBox();//������Ϸ���� 4*4������				 
int *add(int item[]); //�ϲ�����  
int ifMove(int item[]);//�ж��ܷ��ƶ����֣�����1�ܶ���0���ܶ�					  
int if2n(int x); //�ж�x�Ƿ���2��n�η������ǣ�����1�����򷵻�0			 
int ifup();//�ж��Ƿ��ܹ����ƣ��������ƣ�����1�������ƶ����򷵻�0  
int ifdown(); //�ж��Ƿ��ܹ�����  �������ƣ��򷵻�1  �����ƶ����򷵻�0		  
int ifleft();//�ж��Ƿ��ܷ�����  �������ƣ��򷵻�1�� �����ƶ�������0	 
int ifright();//�ж��Ƿ��ܹ�����  �������ƣ��򷵻�1  �����ƶ����򷵻�0		  
int BOXmax();//�������������		 
int gameFaile();//�ж��Ƿ�ʧ��	
int gameWin();//�ж��Ƿ�ʤ��	 
int keyboardControl(int key); //���̿����ƶ�						
void close();  //�˳�		   
void gamePlay();//��ʼ��Ϸ			
void replay();//���¿�ʼ��Ϸ		 
void title(); //���ñ���		  
void choice();//�˵�ѡ��
void choice(); //�˵�ѡ��


//������
int main()
{
// 	for(;;)
// 	if (_kbhit())
// 	{
// 		char str = _getch();
// 		//printf("%c", str);
// 		printf("%d", str);
// 	}

	title(); //��ӡ����
	choice(); //�˵�ѡ��

	return 0;
}


//��ȡ��Ļ���λ��
void setPos(int x, int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//������ɫ����
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
	return 0;
}

//���������޸���ɫ
int textColor(int number)
{
	switch (number)
	{
	case 2:
		return color(12);
		break;
	case 4:
		return color(11);
		break;
	case 8:
		return color(10);
		break;
	case 16:
		return color(14);
		break;
	case 32:
		return color(6);
		break;
	case 64:
		return color(5);
		break;
	case 128:
		return color(4);
		break;
	case 256:
		return color(3);
		break;
	case 512:
		return color(2);
		break;
	case 1024:
		return color(9);
		break;
	case 2048:
		return color(7);
		break;
	}
	return 0;
}

//������Ϸ���� 4*4������
void drawTheGameBox()
{
	int i, j, k;
	setPos(16, 1); //��Ļ����λ��
	color(11);  //��ǳ��ɫ
	printf("��Ϸ������%ld", score);
	color(13); //��ɫ
	setPos(42, 1); //��Ļ����λ��
	printf("ִ�в���: %d\n", step);
	color(14); //��ɫ
	for (j = 2; j <= 22; j += 5) //��ӡ���̱߿�
	{
		setPos(15, j);
		for (k = 1; k < 42; k++)
		{
			printf("-");
		}
		printf("\n");
	}
	for (i = 3; i < 7; i++)
	{
		setPos(15, i);
		printf("|         |         |         |         | ");
	}
	for (i = 8; i < 12; i++)
	{
		setPos(15, i);
		printf("|         |         |         |         | ");
	}
	for (i = 13; i < 17; i++)
	{
		setPos(15, i);
		printf("|         |         |         |         | ");
	}
	for (i = 18; i < 22; i++)
	{
		setPos(15, i);
		printf("|         |         |         |         | ");
	}
	setPos(44, 23);
	color(10); //��ɫ
	printf("����ʱ��%lld s", time(NULL) - Time); //�����Ϸ����ʱ��
}

//�ϲ�����
int *add(int item[])
{
	int i = 0, j = 0;
	int tep[4] = { 0, 0, 0, 0 }, tmp[4] = { 0, 0, 0, 0 };
	for (i = 0; i < 4; i++)
	{
		if (item[i] != 0) //������������������
		{
			tep[j++] = item[i];
		}
	}
	//���������ڵ���ͬ�����ּ�����
	for (i = 0; i < 4; i++)
	{
		if (tep[i] == tep[i + 1]) //�������������ͬ����ϲ�
		{
			tep[i] *= 2; //һ�������е����ַ�������һ��Ϊ��
			tep[i + 1] = 0;
			score = score + tep[i]; //�ӷ֣��ӵķ���Ϊ���������� *2
		}
	}
	j = 0;
	for (i = 0; i < 4; i++)
	{
		if (tep[i] != 0) //���������������
		{
			tmp[j++] = tep[i];
		}
	}

// 	for (i = 0;i < 4;++i)
// 		item[i] = tmp[i];
	return (int *)(&tmp);
}

//�ж��ܷ��ƶ����֣�����1�ܶ���0���ܶ�
int ifMove(int item[])
{
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		//�����Ϊ�ղ���������ͬ
		if (item[i] != 0 && item[i] == item[i + 1])
		{
			return 1;
		}
		//���Ϊ�գ����ڲ�ͬ
		if (item[i] == 0 && item[i + 1] != 0)
		{
			return 1;
		}
	}
	return 0;  //���ܺϲ�������0
}

//�ж�x�Ƿ���2��n�η������ǣ�����1�����򷵻�0
int if2n(int x)
{
	int flag = 0;
	int n;
	int N = 1;
	for (n = 1; n <= 11; n++) //2��11�η���2048
	{
		if (x == pow(2, n)) //����2��n�η�
		{
			flag = 1;
			if (n > N)
				N = n;
			return flag;
		}
	}
	return flag;
}

//�ж��Ƿ��ܹ����ƣ��������ƣ�����1�������ƶ����򷵻�0
int ifup()
{
	int i, j;
	int flag = 0; //�����־������ֻ��0��1
	for(j = 0; j < 4; j++)
		for (i = 0; i < 3; i++)
		{
			//��������������������2��n�η�����������ĸ���������
			if ((if2n(BOX[i][j] + BOX[i + 1][j]) == 1) && BOX[i + 1][j])
			{
				flag = 1;  //��������
			}
		}
	return flag;
}

//�ж��Ƿ��ܹ�����  �������ƣ��򷵻�1  �����ƶ����򷵻�0
int ifdown()
{
	int i, j;
	int flag = 0;
	for(j = 0; j < 4; j++)
		for (i = 3; i > 0; i--)
		{
			//��������������������2��n�η�����������ĸ���������
			if ((if2n(BOX[i][j] + BOX[i - 1][j]) == 1) && BOX[i - 1][j])
			{
				flag = 1; //��������
			}
		}
	return flag;
}

//�ж��Ƿ��ܷ�����  �������ƣ��򷵻�1�� �����ƶ�������0
int ifleft()
{
	int i, j;
	int flag = 0;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
		{
			//��������������������2��n�η�����������ĸ���������
			if ((if2n(BOX[i][j] + BOX[i][j + 1]) == 1) && BOX[i][j + 1])
			{
				flag = 1; //��������
			}
		}
	return flag;
}

//�ж��Ƿ��ܹ�����  �������ƣ��򷵻�1  �����ƶ����򷵻�0
int ifright()
{
	int i, j;
	int flag = 0;
	for(i = 0; i < 4; i++)
		for (j = 3; j > 0; j--)
		{
			//��������������������2��n�η�����������ĸ���������
			if ((if2n(BOX[i][j] + BOX[i][j - 1]) == 1) && BOX[i][j - 1])
			{
				flag = 1; //��������
			}
		}
	return flag;
}

//�������������
int BOXmax()
{
	int max = BOX[0][0]; //��ʼ��BOX����
	int i, j;
	for (i = 0; i < 4; i++)  //������������
	{
		for (j = 0; j < 4; j++)
		{
			if (BOX[i][j] > max) //�������������ֵ����max
			{
				max = BOX[i][j]; //�������е�ֵ��ֵ��max
			}
		}
	}
	return max; //���������е����ֵ
}

//�ж��Ƿ�ʧ��
int gameFaile()
{
	int flag = 0;
	int max;
	//���������Ҳ����ƶ���ʱ����Ϸʧ��
	if (ifup() + ifdown() + ifleft() + ifright() == 0)
	{
		system("cls");
		setPos(34, 3);
		color(14);
		printf("�ϲ�����������ǣ�");
		setPos(52, 3);
		color(11);
		max = BOXmax();
		printf("%d", max);
		setPos(19, 6);
		color(4);   //����ɫ
		printf("     ����������    ��         ��    ����     \n");  //���end�ַ���
		setPos(19, 7);
		printf("     ��            ����       ��    ��  ��   \n");
		setPos(19, 8);
		printf("     ��            �� ��      ��    ��    ��   \n");
		setPos(19, 9);
		printf("     ��            ��  ��     ��    ��     ��  \n");
		setPos(19, 10);
		printf("     ��������      ��   ��    ��    ��      ��  \n");
		setPos(19, 11);
		printf("     ��            ��    ��   ��    ��     ��  \n");
		setPos(19, 12);
		printf("     ��            ��     ��  ��    ��    ��   \n");
		setPos(19, 13);
		printf("     ��            ��      �� ��    ��  ��  \n");
		setPos(19, 14);
		printf("     ����������    ��       ����    ����     \n");
		setPos(34, 17);
		color(13);
		printf("�޷��ƶ�����Ϸʧ�ܣ�");
		flag = 1;
	}
	return flag; //flag��ֵ������0������1���ʾ��Ϸʧ��
}

//�ж��Ƿ�ʤ��
int gameWin()
{
	int flag = 0; 
	//��������е����ֵΪ2048���ﵽĿ�꣬����Ϸʤ��
	if (BOXmax() == 2048)
	{
		setPos(1, 6);
		color(2);   //����ɫ
		printf("     ��             ��             ��       ����������       ��          ��  \n");  //���ʤ��win���ַ���
		setPos(1, 7);
		printf("      ��           ����           ��            ��           �� ��       ��  \n");
		setPos(1, 8);
		printf("       ��         ��  ��         ��             ��           ��  ��      ��  \n");
		setPos(1, 9);
		printf("        ��       ��    ��       ��              ��           ��   ��     ��   \n");
		setPos(1, 10);
		printf("         ��     ��      ��     ��               ��           ��    ��    ��  \n");
		setPos(1, 11);
		printf("          ��   ��        ��   ��                ��           ��     ��   �� \n");
		setPos(1, 12);
		printf("           �� ��          �� ��                 ��           ��      ��  ��    \n");
		setPos(1, 13);
		printf("            ����          ����                  ��           ��       �� ��  \n");
		setPos(1, 14);
		printf("             ��            ��               ����������       ��          ��   \n");
		setPos(35, 17);
		color(13);
		printf("ʤ�����������������");
		flag = 1;
	}
	return flag; //flag��ֵ������0������1���ʾ��Ϸʤ��
}

//���̿����ƶ�
int keyboardControl(int key)
{
	int i = 0, j = 0;
	int *p;
	int tp[4] = { 0, 0, 0, 0 };
	//left = 75, up = 72, down = 80, right = 77
	switch (key)
	{
	
	case 72://up
		j = 0;
		for (i = 0; i < 4; i++)
		{
			tp[0] = BOX[0][i]; //��һ�����Ƶ��м����
			tp[1] = BOX[1][i];
			tp[2] = BOX[2][i];
			tp[3] = BOX[3][i];
			p = add(tp); //��úϲ������ֵ
			//�ж��Ƿ�����ƶ��������ƶ������³���һ������
			//�����ƶ����������ˣ�Ҳ�������������
// 			if (!ifMove(tp))
// 			{
// 				j++; //�����ƶ�
// 			}
			BOX[0][i] = p[0]; //�Ѵ���õ��м�����ƻ���
			BOX[1][i] = p[1];
			BOX[2][i] = p[2];
			BOX[3][i] = p[3];
		}
		return j != 4; //��j������4��ʱ�򣬿���ִ��up����
	case 80: //down
		j = 0; 
		for (i = 0; i < 4; i++)
		{
			tp[0] = BOX[3][i];
			tp[1] = BOX[2][i];
			tp[2] = BOX[1][i];
			tp[3] = BOX[0][i];
			p = add(tp);
// 			if (!ifMove(tp))
// 			{
// 				j++;
// 			}
			BOX[3][i] = p[0];
			BOX[2][i] = p[1];
			BOX[1][i] = p[2];
			BOX[0][i] = p[3];
		}
		return j != 4;
	case 75: //left
		j = 0;
		for (i = 0; i < 4; i++)
		{
			tp[0] = BOX[i][0];
			tp[1] = BOX[i][1];
			tp[2] = BOX[i][2];
			tp[3] = BOX[i][3];
			p = add(tp);
// 			if (!ifMove(tp))
// 			{
// 				j++;
// 			}
			BOX[i][0] = p[0];
			BOX[i][1] = p[1];
			BOX[i][2] = p[2];
			BOX[i][3] = p[3];
		}
		return j != 4;
	case 77: //right
		j = 0;
		for (i = 0; i < 4; i++)
		{
			tp[0] = BOX[i][3];
			tp[1] = BOX[i][2];
			tp[2] = BOX[i][1];
			tp[3] = BOX[i][0];
			p = add(tp);
// 			if (!ifMove(tp))
// 			{
// 				j++;
// 			}
			BOX[i][3] = p[0];
			BOX[i][2] = p[1];
			BOX[i][1] = p[2];
			BOX[i][0] = p[3];
		}
		return j != 4;
	case 27: //��Esc
		setPos(20, 23);
		color(12);
		printf("ȷ���˳���Ϸô��(y/n)");
		char c = _getch();  //��ü�������
		if (c == 'y' || c == 'Y') //����������Сд���д��y
		{
			exit(0);  //�˳���Ϸ
		}
		if (c == 'n' || c == 'N')  //���������Ǵ�д��Сд��n
		{
			setPos(20, 23);
			printf("                        ");
		}
		break;
	default: return 0;
	}
	return 1;
}


//�˳�
void close()
{
	exit(0);
}

//��ʼ��Ϸ
void gamePlay()
{
	system("cls");  //����
	int i = 0, j = 0;
	Time = time(NULL); //ȡ��ǰʱ��Ϊ��ʼʱ��
	drawTheGameBox(); //������Ϸ����
	int a, b; //BOX[][]����ĺ�������
	srand((unsigned)time(NULL)); //�������������
	do 
	{
		//���4*4�����е����λ��
		a = rand() % 4;
		b = rand() % 4;
	} while (BOX[a][b] != 0); //һֱ��������û�пո�

	if (rand() % 4 == 0)  //2��4��������ڿո�
	{
		BOX[a][b] = 4;
	}
	else
	{
		BOX[a][b] = 2;
	}

	for (i = 0; i < 4; i++)  //������������
	{
		for (j = 0; j < 4; j++)
		{
			if (BOX[i][j] == 0) //����������п�λ
			{
				continue;
			}
			setPos(15 + j * 10 + 5, 2 + i * 5 + 3);
			int c = BOX[i][j]; //���������BOX[i][j]�ϵ�����
			printf("%d", c);
		}
	}

	while (1)
	{
		while (_kbhit()) //��鵱ǰ�Ƿ��м������룬�з���1�����򷵻�0
		{
			//������µİ���������keyboardControl()�����ж���ģ���û�з�Ӧ
			//һֱ�����¶���İ���Ϊֹ
			if (!keyboardControl(_getch()))
			{
				continue;
			}
			drawTheGameBox(); //��������
			for (i = 0; i < 4; i++)
			{//��������
				for (j = 0; j < 4; j++)
				{
					if (BOX[i][j] == 0) //����������п�λ�����һֱ���а���
					{
						continue;
					}
					setPos(15 + j * 10 + 5, 2 + i * 5 + 3); //�ϲ���������ֵ�λ��
					int c = BOX[i][j];
					textColor(c);
					printf("%d", c);
				}
			}
			do 
			{ //������λ��
				a = rand() % 4;
				b = rand() % 4;
			} while (BOX[a][b] != 0);

			if (rand() % 4 == 0) //2��4��������ڿո�
			{
				BOX[a][b] = 4; 
			}
			else
			{
				BOX[a][b] = 2;
			}
			step++;  //���мƲ�
			setPos(15 + b * 10 + 5, 2 + a * 5 + 3);
			int c = BOX[a][b];
			textColor(c);
			printf("%d", c);
		}
		//ֻҪgamefaile()����gamewin()����һ����������1��
		//Ҳ���ǳɹ�����ʧ�ܶ���������������
		if (gameFaile() + gameWin() != 0)
		{
			int n;
			setPos(20, 20);
			color(12);
			printf("��Ҫ������һ��-------1");
			setPos(45, 20);
			printf("�����ˣ��˳���-------2\n");
			setPos(43, 21);
			color(11);
			scanf_s("%d", &n);
			switch (n)
			{
			case 1:
				replay(); //������Ϸ����
				break;
			case 2:
				close();
				break;
			}
		}
	}
}

//���¿�ʼ��Ϸ
void replay()
{
	system("cls");
	score = 0, step = 0; //��������������
	memset(BOX, 0, 16 * sizeof(int)); //��ʼ��BOX����
	gamePlay();  //��ʼ��Ϸ
}

//���ñ���
void title()
{
	color(11);          //ǳ����ɫ
	system("title 2048 Online");
	setPos(19, 2);
	printf("������   ��������   ��  ��     ��������"); //���2048�ַ���
	setPos(19, 3);
	printf("    ��   ��    ��   ��  ��     ��    ��");
	setPos(19, 4);
	printf("������   ��    ��   ��  ��     ��������");
	setPos(19, 5);
	printf("��       ��    ��   ��������   ��    ��");
	setPos(19, 6);
	printf("������   ��������       ��     ��������");
}


//�˵�ѡ��
void choice()
{
	int n;
	int i, j = 1;
	setPos(32, 8);
	color(13);
	printf("�� ս 2 0 4 8");
	color(14);  //��ɫ�߿�
	for (i = 9; i <= 20; i++)
	{
		for (j = 15; j <= 60; j++)
		{
			setPos(j, i);
			if (i == 9 || i == 20) printf("�T");
			else if (j == 15 || j == 59) printf("�U");
		}
	}
	color(12);
	setPos(25, 12);
	printf("1.��ʼ��Ϸ");
	setPos(40, 12);
	printf("2.��Ϸ����");
	setPos(25, 16);
	printf("3.����˵��");
	setPos(40, 16);
	printf("4.�˳�");
	setPos(21, 22);
	color(5);
	printf("��ѡ��[1 2 3 4]:[ ]\b\b");
	scanf_s("%d", &n); //����ѡ��
	switch (n)
	{
	case 1:
		gamePlay(); //��Ϸ��ʼ����
		break;
	case 2:
	
		break;
	case 3:
		
		break;
	case 4:
		close();  //�ر���Ϸ����
		break; 
	}

}



