#define SIZE 9
#define UNASSIGNED 0

class Sudoku
{
	public:
		void giveQuestion();
		void readIn();
		void solve();
		void changeNum(int a,int b);
		void changeRow(int a,int b);
		void changeCol(int a,int b);
		void rotate(int n);
		void change();
		void flip(int n);
		void transform();
		void printOut(int grid[SIZE][SIZE]);
		bool Try(int board[SIZE][SIZE]);
		bool Try_backward(int board[SIZE][SIZE]);
		bool findUnassigned(int board[SIZE][SIZE],int &row,int &col);
		bool usedInRow(int board[SIZE][SIZE],int row,int num);
		bool usedInCol(int board[SIZE][SIZE],int col,int num);
		bool usedInCell(int board[SIZE][SIZE],int cellStartRow,int cellStartCol,int num);
		bool isLegal(int board[SIZE][SIZE],int row,int col,int num);
		bool preChkRow(int board[SIZE][SIZE]);
		bool preChkCol(int board[SIZE][SIZE]);
		bool preChkCell(int board[SIZE][SIZE]);
		bool isSolvable(int board[SIZE][SIZE]);

		int board[SIZE][SIZE];
		int rotate_board[SIZE][SIZE];
		int flip_board[SIZE][SIZE];
		int chk_board[SIZE][SIZE];
		int rowFlag[9];
		int colFlag[9];
		int cellFlag[9];
};


