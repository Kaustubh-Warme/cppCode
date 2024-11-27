#include <iostream>
using namespace std;

#define N 4


void printSolution(int board[N][N])
{
    for (int i=0; i<N; i++)
	{
        for (int j=0; j<N; j++)
		{
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


bool isSafe(int board[N][N], int row, int col)
{
    for (int i = 0; i < row; i++)
	{
        if (board[i][col] == 1)
            return false;
    }

    
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
	{
        if (board[i][j] == 1)
            return false;
    }

    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
	{
        if (board[i][j] == 1)
            return false;
    }

    return true;
}


void solveNQueen(int board[N][N], int row, int &solutionCount)
{
    if (row >= N)
	{
        solutionCount++;
        cout << "Solution " << solutionCount << ":\n";
        printSolution(board);
        return;
    }

    for (int col = 0; col < N; col++) 
	{
        if (isSafe(board, row, col))
		{
            board[row][col] = 1; 
            solveNQueen(board, row + 1, solutionCount);
            board[row][col] = 0; 
        }
    }
}

int main()
{
    int board[N][N] = {0}; 
    int solutionCount = 0;

    solveNQueen(board, 0, solutionCount);

    if (solutionCount == 0)
	{
        cout << "Solution does not exists" << endl;
    } else
	{
        cout << "Total solutions: " << solutionCount << endl;
    }

    return 0;
}
