#include<stdio.h>
int Fetters[3][3] = {0,0,0,0,0,0,0,0,0}; //���̾���

int main() //������
{
	int number = 0; //��Ϸѭ������
	int people_array[5] = {0,0,0,0,0}; //��¼����
	int who = 5; //���
	int vs = 0; //�ж�ʤ��������
	/*-------�����Ķ���--------*/

	void print_interface(); //��ӡ����
	void Coordinate(int x,int y); //������
	void State_Update(int people_array[],int who); //״̬����
	void print_command(int people_array[],int who); //����ָ��
	int The_outcome(int vs); //�ж�ʤ��
	/*------------������ʼ��------------*/

	print_interface();
	for (number = 0;number <= 9;number++)
	{
		State_Update(people_array,who); //״̬����
		print_command(people_array,who); //����ָ��
		vs = The_outcome(vs); //�ж�ʤ��
		if(people_array[4] == 1)
			people_array[4] = 0;
		else if(people_array[4] == 0)
			people_array[4] = 1;
		if(vs == 1) //����ֳ�ʤ�������������ѭ��
		{
			Coordinate(15,14);
			printf("��Ӯ��");
			break;
		}
		else if(vs == 2)
		{
			Coordinate(15,14);
			printf("��Ӯ��");
			break;
		}
	}
	if(vs == 0)
	{
		Coordinate(15,14);
		printf("����");
	}
	/*-----------��������----------*/

	return 0;
}

void Coordinate(int x,int y) //������
{
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,pos);
}

void print_interface()  //��ӡ����
{
	system("mode con cols=60 lines=20");
	Coordinate(13,2);
	printf("�X�T�j�T�j�T�[");
	Coordinate(13,3);
	printf("�U  �U  �U  �U");
	Coordinate(13,4);
	printf("�d�T�p�T�p�T�g");
	Coordinate(13,5);
	printf("�U  �U  �U  �U");
	Coordinate(13,6);
	printf("�d�T�p�T�p�T�g");
	Coordinate(13,7);
	printf("�U  �U  �U  �U");
	Coordinate(13,8);
	printf("�^�T�m�T�m�T�a");
}

void State_Update(int people_array[],int who) //״̬����
{
	/*------Բ�����-------*/
	Coordinate(35,2);
	printf("�����");
	Coordinate(33,3);
	printf("��һ����%d,%d",people_array[0],people_array[1]);

	/*-------���������-------*/
	Coordinate(35,6);
	printf("�����");
	Coordinate(33,7);
	printf("��һ��: %d,%d",people_array[2],people_array[3]);

	/*-----�ֵ��Ǹ�����ˣ�------*/

	/*---Բ�����----*/
	if(people_array[4] == 0)
	{
		Coordinate(31,1);
		printf("�X");
		Coordinate(46,1);
		printf("�[");
		Coordinate(31,4);
		printf("�^");
		Coordinate(46,4);
		printf("�a");

		Coordinate(31,5);
		printf("  ");
		Coordinate(46,5);
		printf("  ");
		Coordinate(31,8);
		printf("  ");
		Coordinate(46,8);
		printf("  ");
	}
	/*-----���������----*/
	else if(people_array[4] == 1)
	{
		Coordinate(31,5);
		printf("�X");
		Coordinate(46,5);
		printf("�[");
		Coordinate(31,8);
		printf("�^");
		Coordinate(46,8);
		printf("�a");

		Coordinate(31,1);
		printf("�X");
		Coordinate(46,1);
		printf("�[");
		Coordinate(31,4);
		printf("�^");
		Coordinate(46,4);
		printf("�a");

	}
}

void print_command(int people_array[],int who) //����ָ��
{
	int one = 0; //���뻺����
	int two = people_array[4],three = 0; //�жϴ洢
	/*����к�*/
	do
	{
		do
		{
			do
			{
				Coordinate(25,11);
				printf("  ");
				Coordinate(25,10);
				printf("  ");
				Coordinate(13,10);
				printf("�������к�:");
				Coordinate(13,11);
				printf("�������кţ�");
				Coordinate(25,10);
				if(one != 0)
				{
					scanf("%*[^\n]");
					scanf("%*c");
				}
				one = 1;
				if(two == 0)
				{
					three = 0;
				}
				else if(two == 1)
				{
					three = 2;
				}
			}while(!scanf("%d",&people_array[three]));
		}while(people_array[three] < 1 || people_array[three] > 3);
		/*����к�*/
		do
		{
			do
			{
				Coordinate(25,11);
				printf("  ");
				Coordinate(13,10);
				printf("�������к�:");
				Coordinate(13,11);
				printf("�������кţ�");
				Coordinate(25,11);
				if(one != 0)
				{
					scanf("%*[^\n]");
					scanf("%*c");
				}
				one = 1;
				if(two == 0)
				{
					three = 1;
				}
				else if(two == 1)
				{
					three = 3;
				}
			}while(!scanf("%d",&people_array[three]));
		}while(people_array[three] < 1 || people_array[three] > 3);
	}while(Fetters[people_array[0] - 1][people_array[1] - 1] != 0 && Fetters[people_array[2] - 1][people_array[3] - 1] != 0);

	/*��¼���̣�����������Ӵ�ӡ��������*/
	if(two == 0)
	{
		Fetters[people_array[0] - 1][people_array[1] - 1] = 1;
	}
	else if(two == 1)
	{
		Fetters[people_array[2] - 1][people_array[3] - 1] = 2;
	}
	/*----------��ӡ����---------*/
	
	int m_one = 0,m_two = 0;
	int a = 0,b = 0;
	for(m_one = 3;m_one <= 7;m_one = m_one + 2)
	{
		for(m_two = 15;m_two <= 25;m_two = m_two + 4)
		{
			Coordinate(m_two,m_one);
			if(Fetters[a][b] == 0)
			{
				printf("  ");
			}
			else if(Fetters[a][b] == 1)
			{
				printf("��");
			}
			else if(Fetters[a][b] == 2)
			{
				printf("��");
			}
			b++;
		}
		a++;
		b = 0;
	}
}

int The_outcome(int vs) //�ж�ʤ��
{
	if(Fetters[0][0] == Fetters[0][1] && Fetters[0][1] == Fetters[0][2] && Fetters[0][0] != 0)
	{
		if(Fetters[0][0] == 1)
		{
			vs = 1;
		}
		else if(Fetters[0][0] == 2)
		{
			vs = 2;
		}
	
	}
	if(Fetters[1][0] == Fetters[1][1] && Fetters[1][1] == Fetters[1][2] && Fetters[1][1] != 0)
	{
		if(Fetters[1][0] == 1)
		{
			vs = 1;
		}
		else if(Fetters[1][0] == 2)
		{
			vs = 2;
		}
	}
	if(Fetters[2][0] == Fetters[2][1] && Fetters[2][1] == Fetters[2][2] && Fetters[2][2] != 0)
	{
		if(Fetters[2][0] == 1)
		{
			vs = 1;
		}
		else if(Fetters[2][0] == 2)
		{
			vs = 2;
		}
	}
	if(Fetters[0][0] == Fetters[1][0] && Fetters[1][0] == Fetters[2][0] && Fetters[2][0] != 0)
	{
		if(Fetters[0][0] == 1)
		{
			vs = 1;
		}
		else if(Fetters[0][0] == 2)
		{
			vs = 2;
		}
	}
	if(Fetters[0][1] == Fetters[1][1] && Fetters[1][1] == Fetters[2][1] && Fetters[2][1] != 0)
	{
		if(Fetters[0][1] == 1)
		{
			vs = 1;
		}
		else if(Fetters[0][1] == 2)
		{
			vs = 2;
		}
	}
	if(Fetters[0][2] == Fetters[1][2] && Fetters[1][2] == Fetters[2][2] && Fetters[2][2] != 0)
	{
		if(Fetters[0][2] == 1)
		{
			vs = 1;
		}
		else if(Fetters[0][2] == 2)
		{
			vs = 2;
		}
	}
	if(Fetters[0][0] == Fetters[1][1] && Fetters[1][1] == Fetters[2][2] && Fetters[2][2] != 0)
	{
		if(Fetters[0][0] == 1)
		{
			vs = 1;
		}
		else if(Fetters[0][0] == 2)
		{
			vs = 2;
		}
	}
	if(Fetters[0][2] == Fetters[1][1] && Fetters[1][1] == Fetters[2][0] && Fetters[2][0] != 0)
	{
		if(Fetters[0][2] == 1)
		{
			vs = 1;
		}
		else if(Fetters[0][2] == 2)
		{
			vs = 2;
		}
	}
	return vs;
}
