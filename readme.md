利用蒙特卡洛搜索树完成井字棋游戏

一．课程设计题目

     Project3:利用Minimax算法或α-β剪枝算法实现井字棋游戏。

二．井字棋游戏规则

    “井字棋”游戏（又叫“三子棋”），是一款十分经典的益智小游戏，操作简单，娱乐性强。两个玩家，一个打圈(O)，一个打叉(X)，轮流在3乘3的格上打自己的符号，最先以横、直、斜连成一线则为胜。
    如果双方都下得正确无误，将得和局。
这种游戏实际上是由第一位玩家所控制，第一位玩家是攻，第二位玩家是守。

                       图一 X方取胜的情况

                           图二 和局的情况

第一位玩家在角位行第一子的话赢面最大（见图三），只要第二位玩家不是在中间下子，第一位玩家就可以以两粒连线牵制着第二位玩家，然后制造“两头蛇”。

        
                          图三 “两头蛇”情况                             




三．井字棋与人工智能

这种游戏的变化简单，常成为博弈论和赛局树搜寻的教学例子。这个游戏只有765个可能局面，26830个棋局。如果将对称的棋局视作不同，则有255168个棋局。
由于这种游戏的结构简单，这游戏就成为了人工智能的一个好题目。学生都要从既有的玩法中，归纳出游戏的致胜之道，并将策略演绎成为程式，让电脑与用户对奕。
世界上第一个电脑游戏，1952年为EDSAC电脑制作的OXO游戏，就是以该游戏为题材，可以正确无误地与人类对手下棋。

四．设计方案
    
将井字棋游戏设计为人机对弈系统，分别用X代替人（玩家）的棋子,用O代替机（电脑）的棋子。玩家可以选择自己或电脑先下（游戏实际上是由先下的一方所控制），电脑一方是由程序选择对自己最有利的棋局决定下一步，程序利用Minimax算法结合α-β剪枝算法实现电脑的走步。结局有三种情况：玩家赢，电脑赢或平局。
用一个3×3的井字格来显示用户与电脑下的界面，使用提示信息要求用户输入数据。当用户与计算机分出了胜负后，机器会显示出比赛的结果，并由用户选择是否重玩游戏。

五．算法实现

    1.Minimax(极大极小法)算法思想
    (1). 设博弈双方中一方为MAX，另一方为MIN。然后为其中的一方(计算机)找一个最佳走法。
    (2). 为了找到当前棋局的最优走法，需要对各个可能的走法所产生的后续棋局进行比较，同时也要考虑对方可能的走法，并对后续棋局赋予一定的权值（或者称之为分数）。也就是说，以当前棋局为根节点生成一棵博弈树，N步后的棋局作为树的叶子节点。同时从树根开始轮流给每层结点赋予Max和Min的称号。
    (3). 用一个评估函数来分析计算各个后续棋局（即叶子节点）的权值，估算出来的分数为静态估值。要注意将某方获胜的状态节点的评估函数值设为计算机能表示的最大数（无穷大）或最小数（无穷小）以表明在该状态下有一方获胜。
    (4). 当端节点的估值计算出来后，再推算出父节点的得分。推算的方法是：对于处于MAX层的节点，选其子节点中一个最大的得分作为父节点的得分，这是为了使自己在可供选择的方案中选一个对自己最有利的方案；对处于MIN层的节点，选其子节点中一个最小的得分作为父节点的得分，这是为了立足于最坏的情况，这样计算出的父节点的得分为倒推值。
(5） .如此反推至根节点下的第一层孩子，如果其中某个孩子能获得较大的倒推值，则它就是当前棋局最好的走法。

不过在极大极小法中，必须求出所有端点的评估值，当预先考虑的棋步比较多时，计算量会大大增加。因此，α-β剪枝方法是一种效率比较高的方法。在α-β剪枝方法中，采用了两个变量a和β，它们是最终可以获得的对最大评估值和最小评估值的估计值。

α－β剪枝的方法如下：
1、max节点的α值为当前子节点的最大倒推值；
2、min节点的β值为当前子节点的最小倒推值；
3、α－β剪枝的规则如下：
(1)任何max节点n的α值大于或等于它先辈节点的β值，则n以下的分枝可停止搜索，并令节点n的倒推值为α。这种剪枝称为β剪枝。
(2)任何min节点n的β值小于或等于它先辈节点的α值，则n 以下的分支可停止搜索，并令节点n的倒推值为β。这种剪枝技术称为α剪枝。

算法流程图：
                        




































六.程序模块分析

    (1) 程序用一个二维数组chess[3][3]表示一个棋盘。
(2)IsWin()函数:判断某一状态是否胜负已决。返回0表示没有人赢，返回-1表示玩家赢了，返回1表示电脑赢了。
(3)Evaluation()函数:评估函数，主要思想是计算每一行、每一列、斜线中连成3个棋子的有多少个。
(4)AlphaBeta()函数:α－β剪枝算法的实现。获胜的状态节点的评估函数值设为计算机能表示的最大数（无穷大）或最小数（无穷小）以表明在该状态下有一方获胜。
(5)PlayerInput()函数:提示玩家输入，用户通过此函数来选择落子的位置,并提示不正确的输入。
(6)PrintChess()函数:将棋盘以界面的形式显示出来，棋盘的信息存储在一个二维数组chess[3][3]中。
(7)PlayChess()函数:人机对弈模拟过程的实现。

七． 结果演示

1. 初始界面：
（X代替玩家的棋子,用O代替电脑的棋子，□代表空位置）



2.玩家选择谁先走，这里我们让玩家先走：


3. 两者交替走步，直到分出胜负：



    结果分析：上述情况事实上是玩家唯一可以赢电脑的情况，除此之外，玩家至多平局。赢电脑的情况是因为当玩家两个棋子占据棋盘对角的时候，电脑还预测不到玩家的意图，当第三个棋子占据棋盘一角三个棋子成掎角之势时，出现了两种赢的情况，电脑已经守不住了。

附录（程序代码）：

#include<stdio.h>
#include<string.h>

int chess[3][3];
int x,y,count;

int IsWin()
{
	int i;
	for(i=0;i<3;i++)
	{
		if(chess[i][0]==1 && chess[i][1]==1 && chess[i][2]==1) return 1;
		if(chess[i][0]==-1 && chess[i][1]==-1 && chess[i][2]==-1) return -1;
	}

	for(i=0;i<3;i++)
	{
		if(chess[0][i]==1 && chess[1][i]==1 && chess[2][i]==1) return 1;
		if(chess[0][i]==-1 && chess[1][i]==-1 && chess[2][i]==-1) return -1;
	}

	if((chess[0][0]==1&&chess[1][1]==1&&chess[2][2]==1)||(chess[2][0]==1&&chess[1][1]==1&&chess[0][2]==1)) return 1;
    if((chess[0][0]==-1&&chess[1][1]==-1&&chess[2][2]==-1)||(chess[2][0]==-1&&chess[1][1]==-1&&chess[0][2]==-1)) return -1;

	return 0;
}

int Evaluation()
{
	int i,j,temp[3][3];

	x=y=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(chess[i][j]==0) temp[i][j]=1;
			else temp[i][j]=chess[i][j];
		}
	}
 
	for(i=0;i<3;i++)
	{
		x+=(temp[i][0]+temp[i][1]+temp[i][2])/3;
	}

	for(i=0;i<3;i++)
	{
		x+=(temp[0][i]+temp[1][i]+temp[2][i])/3;
	}

	x+=(temp[0][0]+temp[1][1]+temp[2][2])/3;
	x+=(temp[2][0]+temp[1][1]+temp[0][2])/3;

	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(chess[i][j]==0) temp[i][j]=-1;
			else temp[i][j]=chess[i][j];
		}
	}

	for(i=0;i<3;i++)
	{
		y+=(temp[i][0]+temp[i][1]+temp[i][2])/3;
	}

	for(i=0;i<3;i++)
	{
		y+=(temp[0][i]+temp[1][i]+temp[2][i])/3;
	}

	y+=(temp[0][0]+temp[1][1]+temp[2][2])/3;
	y+=(temp[2][0]+temp[1][1]+temp[0][2])/3;

	return x+y;
}

int AlphaBeta(int &value,int deep,bool MAX)
{
	bool prune=false;
	int i,j,flag,temp;        
     
    if(deep==3||deep+count==9)
    {
        return Evaluation();
    }
                
    if(IsWin()==1)
    {
        value=10000;
        return 0;
    }

    if(MAX)                  
        flag=10000;
    else
        flag=-10000;
    for(i=0;i<3 && !prune;i++)
    {
        for(j=0;j<3 && !prune;j++)
        {
            if(chess[i][j]==0)
            {
                if(MAX)
                {
                    chess[i][j]=-1;
                        
                    if(IsWin()==-1)
                        temp=-10000;
                    else
                        temp=AlphaBeta(flag,deep+1,!MAX);

                    if(temp<flag) flag=temp;                      
                    if(flag<=value) prune=true;                      
                }
                else
                {
                    chess[i][j]=1;
                    
                    if(IsWin()==1)
                        temp=10000;
                    else
                        temp=AlphaBeta(flag,deep+1,!MAX);

                    if(temp>flag) flag=temp;                     
                    if(flag>=value) prune=true;
                       
                }
                chess[i][j]=0;
            }
        }
    }
    if(MAX)
    {
        if(flag>value)
            value=flag;
    }
    else
    {
        if(flag<value)
            value=flag;
    }


    return flag;
}

void PlayerInput()
{
	int row,col;
	while(true)
	{
		printf("\nYou move it at(x y):");
		scanf("%d%d",&row,&col);

		if(row>0&&row<4&&col>0&&col<4&&chess[row-1][col-1]==0)
		{
			chess[row-1][col-1]=-1;
			break;
		}
		else
		{
			printf("Input Error!\n");
		}
	}
}

void PrintChess()
{
	int i,j;

	printf("\n");
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(chess[i][j]==1) printf("○");
			if(chess[i][j]==0) printf("□");
			if(chess[i][j]==-1) printf("×");
		}
		printf("\n");
	}
}

int PlayChess()
{
	int row,col,temp;
	int m=-10000,value=-10000,deep=1;
 
	count=0;
	memset(chess,0,sizeof(chess));
	printf("ChessBoard:\n");
	PrintChess();

	while(true)
	{
		printf("\nWho take the first step:\n1)Player.  2)Computer.[ ]\b\b");
		scanf("%d",&temp);
		if(temp!=1 && temp!=2) getchar();
		else break;
	}

	if(temp==1)
	{ 
		while(true)
		{
			PlayerInput();
			PrintChess();
			count++;
			Evaluation();
			
			if(y==0)         
			{
				printf("\nThe game ended in a tie!\n");
				return 0;
			}
			if (IsWin()==-1)
			{
				printf("\nCongratulations,you win!\n");
				return 0;
			}

			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					if(chess[i][j]==0)
					{
						chess[i][j]=1;
						AlphaBeta(value,deep,1);

						if(IsWin()==1)  
						{
							printf("\nComputer put it at:%d %d\n",i+1,j+1);
							PrintChess();
							printf("\nOh,the computer win!\n");
							return 0;
						}

						if(value>m) 
						{
							m=value;
							row=i;col=j;
						}
						value=-10000;
						chess[i][j]=0;
					}
				}
			}
			if(chess[row][col])
			{
				printf("\nCongratulations,you win!\n");
				return 0;
			}
			chess[row][col]=1;
	   
			value=-10000;m=-10000;deep=1;
	        printf("\nComputer put it at:%d %d\n",row+1,col+1);
			PrintChess();
			count++;
			Evaluation();
			
			if(y==0)         
			{
				printf("\nThe game ended in a tie!\n");
				return 0;
			}
		}
	}
	else                                                           
	{
		while(true)
		{
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					if(chess[i][j]==0)
					{
						chess[i][j]=1;
						AlphaBeta(value,deep,1);

						if(IsWin()==1)  
						{
							printf("\nComputer put it at:%d %d\n",i+1,j+1);
							PrintChess();
							printf("\nOh,the computer win!\n");
							return 0;
						}

						if(value>m) 
						{
							m=value;
							row=i;col=j;
						}
						value=-10000;
						chess[i][j]=0;
					}
				}
			}
			chess[row][col]=1;
	   
			value=-10000;m=-10000;deep=1;
	        printf("\nComputer put it at:%d %d\n",row+1,col+1);
			PrintChess();
			count++;
			Evaluation();
			
			if(x==0)         
			{
				printf("\nThe game ended in a tie!\n");
				return 0;
			}			
			PlayerInput();
			PrintChess();
			count++;
			Evaluation();		
			if(x==0)         
			{
				printf("\nThe game ended in a tie!\n");
				return 0;
			}

			if (IsWin()==-1)
			{
				printf("\nCongratulations,you win!.\n");
				return 0;
			}
		}
	}	
	return 0;
}

void main()
{
	int k;
	while(true)
	{
		PlayChess();
		printf("\nTry Again?\n1)Yeah.\t2)Exit.[ ]\b\b");
		scanf("%d",&k); 
		if(k!=1 && k!=2) getchar();
		if(k==2) break;
	}
}
