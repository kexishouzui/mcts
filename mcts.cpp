#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

const int MAX_MOVES = 9;

void printBoard(char board[3][3]);

void getNextMove(char board[3][3]);

void win(char board[3][3]);

void whowin(char key);
int  foot = 0;

int main()
{
  int  i;
  int  n           = 0;
  char board[3][3] = {'7', '8', '9', '4', '5', '6', '1', '2', '3'};

  printBoard(board);

  for (i = 0; i < MAX_MOVES; i++)
  {
    getNextMove(board);
    win(board);
    n++;
  }

  if (n = MAX_MOVES)
    cout << "gameover";

  system("PAUSE");
  return 0;
}
void win(char a[3][3])
{
  int  i, j, k;
  char key;
  if ((a[0][0] == a[1][1] && a[1][1] == a[2][2] && a[2][2] == a[0][0]) || (a[2][0] == a[1][1] && a[1][1] == a[0][2] && a[2][0] == a[0][2]))
  {
    key = a[0][0];
    whowin(key);
  }
  else
  {
    for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
        if (a[i][j] == 15 || a[i][j] == 'X')
        {
          key = a[i][j];
          for (k = 0; k < 3; k++)
          {
            if (a[i][k] != key)
              break;
          }
          if (k == 3)
            whowin(key);
          for (k = 0; k < 3; k++)
          {
            if (a[k][j] != key)
              break;
          }
          if (k == 3)
            whowin(key);
        }
  }
}
void whowin(char key)
{
  if (key == 15)
    cout << "P1 Win!" << endl;
  else
    cout << "P2 Win!" << endl;
  exit(0);
}
void printBoard(char board[3][3])
{
  cout << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << endl;
  cout << "--+---+--" << endl;
  cout << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << endl;
  cout << "--+---+--" << endl;
  cout << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << endl;
}

void getNextMove(char board[3][3])
{
  int  i, j, s, t;
  char m;
  while (1)
  {
    s = -1;
    t = -1;
    cout << "Make your move: ";
    cin >> m;
    for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
        if (board[i][j] == m)
        {
          s = i;
          t = j;
        }
    if (s == -1 && t == -1)
      cout << "that point already has a pawn!" << endl;
    else
      break;
  }
  if (foot % 2 == 0)
    board[s][t] = 15;
  else
    board[s][t] = 'X';
  foot++;
  //system("cls");
  printBoard(board);
}