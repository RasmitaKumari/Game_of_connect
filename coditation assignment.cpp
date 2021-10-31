#include<bits/stdc++.h>
using namespace std;
int board[1001][1001];
int pos[1001];
int rows, column, p;
void initializeGame()
{
  memset(board,0,sizeof(board));
  for(int i=0; i<=column; ++i)
  pos[i] = rows;  // initialize every column with bottom end
}

bool checkRow(int row, int col)
{
  int count = 0;
  int color = board[row][col];
  for(int i=col; i>=1; --i)
  {
    if(board[row][i]==color)
    ++count;
    else
    break;
  }
  for(int i=col+1; i<=column; ++i)
  {
    if(board[row][i]==color)
    ++count;
    else
    break;
  }

  if(count >= p)
  return true;
  return false;
}

bool checkColumn(int row, int col)
{
  int count = 0;
  int color = board[row][col];
  for(int i=row; i>=1; --i)
  {
    if(board[i][col] == color)
    ++count;
    else
    break;
  }
  for(int i=row+1; i<=rows; ++i)
  {
    if(board[i][col] == color)
    ++count;
    else
    break;
  }

  if(count >= p)
  return true;
  return false;
}

bool checkDiagonal1(int row, int col)
{
  int count = 0, color = board[row][col];
  int r = row, c = col;
  while(r>=1 && r<=rows && c>=1 && c<=column && board[r][c]==color)
  {
    ++count;
    --r; --c;
  }
  r = row; c = col;
  while(r>=1 && r<=rows && c>=1 && c<=column && board[r][c]==color)
  {
    ++count;
    ++r; ++c;
  }

  return (count>=p ? true: false);
}

bool checkDiagonal2(int row, int col)
{
  int count = 0, color = board[row][col];
  int r = row, c = col;
  while(r>=1 && r<=rows && c>=1 && c<=column && board[r][c]==color)
  {
    ++count;
    --r; ++c;
  }
  r = row; c = col;
  while(r>=1 && r<=rows && c>=1 && c<=column && board[r][c]==color)
  {
    ++count;
    ++r; --c;
  }

  return (count>=p ? true:false);
}

bool check(int col)
{
  int row = pos[col]+1;
  if(checkRow(row,col))
  return true;

  if(checkColumn(row,col))
  return true;

  if(checkDiagonal1(row,col))
  return true;

  if(checkDiagonal2(row,col))
  return true;

  return false;
}
void play(int &player, bool &flag)
{
  int col;
  while(1)
  {
    cout<<"\nEnter column number- ";
    cin>>col;
    if(col<1 || col>column)
    {
      cout<<"\nInvalid position, play again..";
      continue;
    }
    if(pos[col]==0)
    {
      cout<<"\nThat column is full, choose another column..";
      continue;
    }
    board[pos[col]][col] = player;
    pos[col]--;
    break;
  }
  flag = check(col);
  return ;
}

void print()
{
  for(int i=1; i<=6; ++i)
  {
    for(int j=1; j<=7; ++j)
    cout<<board[i][j]<<" ";
    cout<<"\n";
  }
}

void playGame(int &player1, int &player2)
{
  bool flag1 = false, flag2 = false; // both flag false, means none of the winner
  for(int i=0; i<42; ++i)  // maximum move can be of 42 move
  {
    int move;
    if(i%2==0) {    // player 1 turn
      cout<<"\n\tIts Player1 turn ---";
      play(player1,flag1);
    }
    else {         // player 2 turn
      cout<<"\n\tIts Player2 turn ---";
      play(player2,flag2);
    }
    print();
    if(flag1 || flag2)
    break;
  }

  if(flag1)
  cout<<"\nPlayer1 is the winner..";
  else if(flag2)
  cout<<"\nPlayer2 is the winner..";
  else
  cout<<"\nMatch tie..";

  return ;

}
void inputDimension()
{
  int r,c,p1;
  while(true)
  {
    cout<<"\nEnter row of board - ";
    cin>>r;
    if(r <= 0)
    {
      cout<<"\nRow size cannot be negative..please enter valid dimension..";
      continue;
    }
    if(r >= 1000)
    {
      cout<<"\nRow size exceeded..please enter valid row dimension..";
      continue;
    }
    rows = r;
    break;
  }

  while(true)  // input for column
  {
    cout<<"\nEnter column of board- ";
    cin>>c;
    if(c<=0)
    {
      cout<<"\nColumn cannot be negative..please enter valid dimension..";
      continue;
    }
    if(c > 1000)
    {
      cout<<"\nColumn size exceeded..please enter valid column dimension..";
      continue;
    }
    column = c;
    break;
  }
  while(true)  // input for p connected
  {
    cout<<"\nHow many connected cell for winner- ";
    cin>>p1;
    if(p1<=0)
    {
      cout<<"\nPlease enter valid connected cell for winner..";
      continue;
    }
    if(p1>=1000 || p1 >= max(rows,column))
    {
      cout<<"\nConnected number is out of range..try again..";
      continue;
    }
    p = p1;
    break;
  }
  return ;
}
int main(void)
{
  while(1)
  {
    cout<<"\t\t\t...Connected cell game...\n";
    inputDimension();  // taking input about r-c-p from user
    initializeGame();  // initialize board and player
    int player1, player2;
    while(true)
    {
      cout<<"\nRed : 1 \t Black : -1\n";
      cout<<"\nPlayer1 : which color do you want(choose 1 or -1)- ";
      cin>>player1;
      if(player1 != 1 && player1!=-1)
      {
        cout<<"\nInvalid color number.. please try again..";
        continue;
      }
      player2 = (player1==1 ? -1 : 1);
      break;
    }
    print();
    playGame(player1, player2);
    char ch;
    cout<<"\nDo you want to play again ?(Y/N) : ";
    cin>>ch;
    if(ch=='N' || ch=='n')
    break;
  }
  return 0;
}
