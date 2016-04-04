#include "Sudoku.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void Sudoku::giveQuestion()
{
	int ques[9][9] = {8,0,0,0,0,0,0,0,0,
		0,0,3,6,0,0,0,0,0,
		0,7,0,0,9,0,2,0,0,
		0,5,0,0,0,7,0,0,0,
		0,0,0,0,4,5,7,0,0,
		0,0,0,1,0,0,0,3,0,
		0,0,1,0,0,0,0,6,8,
		0,0,8,5,0,0,0,1,0,
		0,9,0,0,0,0,4,0,0};
	for(int i=0;i<SIZE;i++)
		for(int j=0;j<SIZE;j++)
			board[i][j] = ques[i][j];	
	change();
	printOut(board);
}

void Sudoku::readIn()
{
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			cin>>board[i][j];		
}

bool Sudoku::Try(int board[SIZE][SIZE])
{
	int row,col;
	//If there is no unassigned location,we're finished
	if(!findUnassigned(board,row,col))
		return true;

	for(int num=1;num<=9;num++)
	{
		//if no conflict with sudoku rules
		if(isLegal(board,row,col,num))
		{
			//we try it!!
			board[row][col] = num;
			//return,hopefully success
			if(Try(board))
				return true;			
			//if fail,start over
			board[row][col] = UNASSIGNED;
		}
	}
	return false;//this starts "backtracking"
}

bool Sudoku::Try_backward(int chk_board[SIZE][SIZE])
{
	int row,col;
	//If there is no unassigned location,we're finished
	if(!findUnassigned(chk_board,row,col))
		return true;
	//9~1  (BACKWARDS!!!)
	for(int num=9;num>=1;num--)
	{	
		//if no conflict with Sudoku rule
		if(isLegal(chk_board,row,col,num))
		{
			//We try it!!
			chk_board[row][col] = num;
			//return,hopefully success
			if(Try_backward(chk_board))
				return true;
			//if fail,start over
			chk_board[row][col] = UNASSIGNED;
		}
	}
	return false;//this starts backtracking
}

/* search the board for a space that is unassigned, if found,then the space will be set "unassigned",and true is returned. Ifunassigned not found, false is returned*/
bool Sudoku::findUnassigned(int board[SIZE][SIZE],int &row,int &col)
{
	for(row=0;row<SIZE;row++)
		for(col=0;col<SIZE;col++)
			if(board[row][col]==UNASSIGNED)
				return true;
}

/*returns boolean whether any "assigned" space within each row matches the given number*/
bool Sudoku::usedInRow(int board[SIZE][SIZE],int row,int num)
{
	for(int col=0;col<SIZE;col++)
		if(board[row][col]==num)
			return true;
	return false;
}

/*returns boolean whether any "assigned" space within each column matches the given number*/
bool Sudoku::usedInCol(int board[SIZE][SIZE],int col,int num)
{
	for(int row=0;row<SIZE;row++)
		if(board[row][col]==num)
			return true;
	return false;
}

/*returns boolean whether any "assigned" space within each cell matches the given number*/
bool Sudoku::usedInCell(int board[SIZE][SIZE],int cellStartRow,int cellStartCol,int num)
{
	for(int row=0;row<(SIZE/3);row++)
		for(int col=0;col<(SIZE/3);col++)
			if(board[row+cellStartRow][col+cellStartCol]==num)
				return true;
	return false;
}
/*returns boolean to check if we can fill this number in the space*/
bool Sudoku::isLegal(int board[SIZE][SIZE],int row,int col,int num)
{
	/*check if "num" is already placed in same row,col,or cell(just call function!!)*/
	return !usedInRow(board,row,num) && !usedInCol(board,col,num) && !usedInCell(board,row-row%3,col-col%3,num);
}

bool Sudoku::preChkRow(int board[SIZE][SIZE])
{
	int rowFlag[9]={0,0,0,0,0,0,0,0,0};
	for(int i=0;i<SIZE;i++)
	{	
		for(int num=1;num<=9;num++)
		{
			if(board[0][i]==num)
				rowFlag[num-1]++;
			if(board[1][i]==num)
				rowFlag[num-1]++;
			if(board[2][i]==num)
				rowFlag[num-1]++;
			if(board[3][i]==num)
				rowFlag[num-1]++;	
			if(board[4][i]==num)
				rowFlag[num-1]++;
			if(board[5][i]==num)
				rowFlag[num-1]++;
			if(board[6][i]==num)
				rowFlag[num-1]++;
			if(board[7][i]==num)
				rowFlag[num-1]++;
			if(board[8][i]==num)
				rowFlag[num-1]++;
		}
		for(int i=0;i<SIZE;i++)
		{
			if(rowFlag[i]>1)
				return true;
			else
				rowFlag[i] = 0;
		}

	}
	/*****/
	//cout<<"rowFlag:"<<endl;
	//for(int i=0;i<9;i++)
	//cout<<rowFlag[i]<<" ";
	//cout<<endl;
	/*****/
	return false;
}

bool Sudoku::preChkCol(int board[SIZE][SIZE])
{
	int colFlag[9]={0,0,0,0,0,0,0,0,0};
	for(int i=0;i<SIZE;i++)
	{	
		for(int num=1;num<=9;num++)
		{
			if(board[i][0]==num)
				colFlag[num-1]++;
			if(board[i][1]==num)
				colFlag[num-1]++;
			if(board[i][2]==num)
				colFlag[num-1]++;
			if(board[i][3]==num)
				colFlag[num-1]++;	
			if(board[i][4]==num)
				colFlag[num-1]++;
			if(board[i][5]==num)
				colFlag[num-1]++;
			if(board[i][6]==num)
				colFlag[num-1]++;
			if(board[i][7]==num)
				colFlag[num-1]++;
			if(board[i][8]==num)
				colFlag[num-1]++;
		}
		for(int i=0;i<SIZE;i++)
		{
			if(colFlag[i]>1)
				return true;
			else
				colFlag[i] = 0;
		}
	}
	/*****/
	//cout<<"colFlag:"<<endl;
	//for(int i=0;i<9;i++)
	//cout<<colFlag[i]<<" ";
	//cout<<endl;
	/*****/
	return false;
}

bool Sudoku::isSolvable(int board[SIZE][SIZE])
{
	if(preChkRow(board))
		return false;
	if(preChkCol(board))
		return false;
	return true;
}

void Sudoku::solve()
{
	if(!isSolvable(board))
	{
		cout<<"0"<<endl;
		exit(1);
	}
	for(int i=0;i<SIZE;i++)
		for(int j=0;j<SIZE;j++)
			chk_board[i][j] = board[i][j];

	int flag[SIZE][SIZE];
	/*solve "board" and "chk_board"*/
	if(Try(board) && Try_backward(chk_board))
	{
		for(int i=0;i<SIZE;i++)
		{
			for(int j=0;j<SIZE;j++)
			{
				/*if the two board is same, set flag to 1*/
				if(board[i][j]==chk_board[i][j])
					flag[i][j] = 1;
				else
					flag[i][j] = 0;
			}
		}
	}
	else
	{
		cout<<"0"<<endl;
		exit(1);
	}

	/*loop check flag value*/
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			if(flag[i][j]==0)
			{
				cout<<"2"<<endl;
				exit(1);
			}
		}
	}
	/*if none of the conditons occured above, then unique solution*/
	cout<<"1"<<endl;
	printOut(board);

}

void Sudoku::changeNum(int a,int b)
{
	int tmp_board[SIZE][SIZE];

	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
			tmp_board[i][j] = board[i][j];
	}
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(board[i][j]==a)
				board[i][j] = b;
			if(tmp_board[i][j]==b)
				board[i][j] = a;
		}
	}

}

void Sudoku::changeRow(int a,int b)
{
	while(a!=b)
	{
		if(a == 0){
			if(b == 1)
			{
				for(int i=0;i<9;i++)
				{
					swap(board[3][i],board[0][i]);
					swap(board[4][i],board[1][i]);
					swap(board[5][i],board[2][i]);		
				}
			}
			else if(b == 2)
			{
				for(int i=0;i<9;i++)
				{
					swap(board[6][i],board[0][i]);
					swap(board[7][i],board[1][i]);
					swap(board[8][i],board[2][i]);
				}
			}
		}
		if(a == 1){	
			if(b == 0)
			{
				for(int i=0;i<9;i++)
				{
					swap(board[0][i],board[3][i]);
					swap(board[1][i],board[4][i]);
					swap(board[2][i],board[5][i]);		
				}
			}
			else if(b == 2)
			{	
				for(int i=0;i<9;i++)
				{
					swap(board[6][i],board[3][i]);
					swap(board[7][i],board[4][i]);
					swap(board[8][i],board[5][i]);
				}
			}
		}
		if(a == 2)
		{
			if(b == 0)
			{
				for(int i=0;i<9;i++)
				{
					swap(board[0][i],board[6][i]);
					swap(board[1][i],board[7][i]);
					swap(board[2][i],board[8][i]);
				}
			}
			else if(b == 1)
			{	
				for(int i=0;i<9;i++)
				{
					swap(board[3][i],board[6][i]);
					swap(board[4][i],board[7][i]);
					swap(board[5][i],board[8][i]);
				}
			}

		}
		break;
	}
}

void Sudoku::changeCol(int a,int b)
{
	while(a!=b)
	{
		if(a == 0){
			if(b == 1)
			{
				for(int i=0;i<9;i++)
				{
					swap(board[i][0],board[i][3]);
					swap(board[i][1],board[i][4]);
					swap(board[i][2],board[i][5]);
				}
			}
			else if(b == 2)
			{
				for(int i=0;i<9;i++)
				{

					swap(board[i][0],board[i][6]);
					swap(board[i][1],board[i][7]);
					swap(board[i][2],board[i][8]);
				}
			}
		}
		if(a == 1){	
			if(b == 0)
			{
				for(int i=0;i<9;i++)
				{
					swap(board[i][0],board[i][3]);
					swap(board[i][1],board[i][4]);
					swap(board[i][2],board[i][5]);
				}
			}
			else if(b == 2)
			{	
				for(int i=0;i<9;i++)
				{
					swap(board[i][6],board[i][3]);
					swap(board[i][7],board[i][4]);
					swap(board[i][8],board[i][5]);
				}
			}
		}
		if(a == 2)
		{
			if(b == 0)
			{
				for(int i=0;i<9;i++)
				{
					swap(board[i][0],board[i][6]);
					swap(board[i][1],board[i][7]);
					swap(board[i][2],board[i][8]);
				}
			}
			else if(b == 1)
			{	
				for(int i=0;i<9;i++)
				{

					swap(board[i][6],board[i][3]);
					swap(board[i][7],board[i][4]);
					swap(board[i][8],board[i][5]);
				}
			}

		}
		break;
	}

}

void Sudoku::rotate(int n)
{
	for(int k=0;k<n;k++)
	{
		for(int i=0;i<9;i++)
		{
			for(int j=0;j<9;j++)
			{	
				rotate_board[j][8-i] = board[i][j]; 
			}
		}

		for(int i=0;i<9;i++)
		{
			for(int j=0;j<9;j++)
			{
				board[i][j] = rotate_board[i][j];
			}
		}
	}

}

void Sudoku::flip(int n)
{
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(n==0)
				flip_board[i][j] = board[8-i][j];
			else
				flip_board[i][j] = board[i][8-j];

		}
	}
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++)
			board[i][j] = flip_board[i][j];

}
void Sudoku::printOut(int grid[SIZE][SIZE])
{
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			cout<<grid[i][j]<<" ";
		}
		cout<<endl;
	}
}
void Sudoku::change()
{
	srand(time(NULL));
	changeNum(rand()%9+1,rand()%9+1);
	changeRow(rand()%3,rand()%3);
	changeCol(rand()%3,rand()%3);
	rotate(rand()%101);
	flip(rand()%2);
}
void Sudoku::transform()
{
	change();
	printOut(board);	
}


