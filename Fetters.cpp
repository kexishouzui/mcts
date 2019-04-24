#include<stdio.h>
int Fetters[3][3] = {0,0,0,0,0,0,0,0,0}; //棋盘矩阵

int main() //主函数
{
	int number = 0; //游戏循环主体
	int people_array[5] = {0,0,0,0,0}; //记录步骤
	int who = 5; //玩家
	int vs = 0; //判断胜负的依据
	/*-------变量的定义--------*/

	void print_interface(); //打印画面
	void Coordinate(int x,int y); //坐标轴
	void State_Update(int people_array[],int who); //状态更新
	void print_command(int people_array[],int who); //输入指令
	int The_outcome(int vs); //判断胜负
	/*------------函数初始化------------*/

	print_interface();
	for (number = 0;number <= 9;number++)
	{
		State_Update(people_array,who); //状态更新
		print_command(people_array,who); //输入指令
		vs = The_outcome(vs); //判断胜负
		if(people_array[4] == 1)
			people_array[4] = 0;
		else if(people_array[4] == 0)
			people_array[4] = 1;
		if(vs == 1) //如果分出胜负，则结束整个循环
		{
			Coordinate(15,14);
			printf("●赢了");
			break;
		}
		else if(vs == 2)
		{
			Coordinate(15,14);
			printf("▲赢了");
			break;
		}
	}
	if(vs == 0)
	{
		Coordinate(15,14);
		printf("和棋");
	}
	/*-----------函数调用----------*/

	return 0;
}

void Coordinate(int x,int y) //坐标轴
{
	COORD pos = {x,y};
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut,pos);
}

void print_interface()  //打印画面
{
	system("mode con cols=60 lines=20");
	Coordinate(13,2);
	printf("╔═╦═╦═╗");
	Coordinate(13,3);
	printf("║  ║  ║  ║");
	Coordinate(13,4);
	printf("╠═╬═╬═╣");
	Coordinate(13,5);
	printf("║  ║  ║  ║");
	Coordinate(13,6);
	printf("╠═╬═╬═╣");
	Coordinate(13,7);
	printf("║  ║  ║  ║");
	Coordinate(13,8);
	printf("╚═╩═╩═╝");
}

void State_Update(int people_array[],int who) //状态更新
{
	/*------圆形玩家-------*/
	Coordinate(35,2);
	printf("●玩家");
	Coordinate(33,3);
	printf("上一步：%d,%d",people_array[0],people_array[1]);

	/*-------三角形玩家-------*/
	Coordinate(35,6);
	printf("▲玩家");
	Coordinate(33,7);
	printf("上一步: %d,%d",people_array[2],people_array[3]);

	/*-----轮到那个玩家了？------*/

	/*---圆形玩家----*/
	if(people_array[4] == 0)
	{
		Coordinate(31,1);
		printf("╔");
		Coordinate(46,1);
		printf("╗");
		Coordinate(31,4);
		printf("╚");
		Coordinate(46,4);
		printf("╝");

		Coordinate(31,5);
		printf("  ");
		Coordinate(46,5);
		printf("  ");
		Coordinate(31,8);
		printf("  ");
		Coordinate(46,8);
		printf("  ");
	}
	/*-----三角形玩家----*/
	else if(people_array[4] == 1)
	{
		Coordinate(31,5);
		printf("╔");
		Coordinate(46,5);
		printf("╗");
		Coordinate(31,8);
		printf("╚");
		Coordinate(46,8);
		printf("╝");

		Coordinate(31,1);
		printf("╔");
		Coordinate(46,1);
		printf("╗");
		Coordinate(31,4);
		printf("╚");
		Coordinate(46,4);
		printf("╝");

	}
}

void print_command(int people_array[],int who) //输入指令
{
	int one = 0; //输入缓冲区
	int two = people_array[4],three = 0; //判断存储
	/*玩家行号*/
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
				printf("请输入行号:");
				Coordinate(13,11);
				printf("请输入列号：");
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
		/*玩家列号*/
		do
		{
			do
			{
				Coordinate(25,11);
				printf("  ");
				Coordinate(13,10);
				printf("请输入行号:");
				Coordinate(13,11);
				printf("请输入列号：");
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

	/*记录棋盘，吧输入的棋子打印到矩阵中*/
	if(two == 0)
	{
		Fetters[people_array[0] - 1][people_array[1] - 1] = 1;
	}
	else if(two == 1)
	{
		Fetters[people_array[2] - 1][people_array[3] - 1] = 2;
	}
	/*----------打印棋子---------*/
	
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
				printf("●");
			}
			else if(Fetters[a][b] == 2)
			{
				printf("▲");
			}
			b++;
		}
		a++;
		b = 0;
	}
}

int The_outcome(int vs) //判断胜负
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
