#include "Board.h"
#include<string.h>

Board* initialBoard()
{
	Board* newBoard = (Board*)malloc(sizeof(Board));
	checkAlloc(newBoard, "Board Allocation Failed.");
	char player = 'T';
	for (int i = 0; i < 8; i++)
	{
		if (i == 3 || i == 4)
		{
			for (int j = 0; j < 8; j++)
				(*newBoard)[i][j] = ' ';
		}
		else
		{
			if (i % 2 == 0) // row is even
			{
				for (int j = 0; j < 8; j = j + 2)
					(*newBoard)[i][j] = ' ';

				for (int j = 1; j < 8; j = j + 2)
					(*newBoard)[i][j] = player;
			}
			else // row is odd
			{
				for (int j = 0; j < 8; j = j + 2)
					(*newBoard)[i][j] = player;

				for (int j = 1; j < 8; j = j + 2)
					(*newBoard)[i][j] = ' ';
			}
		}

		if (i == 2)
		{
			player = 'B';
		}
	}

	return newBoard;
}

bool isCheckerExist(Board board, checkersPos* pos, Player* player)
{
	char checker = board[CHARTOROW(pos->row)][CHARTOCOL(pos->col)];

	if (checker != ' ')
	{
		*player = checker;
		return true;
	}
	return false;
}

void printBoard(Board board)
{
	printf("+-+-+-+-+-+-+-+-+-+\n");
	printf("+ ");
	for (int i = 1; i < 9; i++)
	{
		printf("|%d", i); 
		(i == 8) ? printf("|") : printf("");
	}
	printf("\n");
	for (int i = 0;i < 8;i++)
	{
		printf("+-+-+-+-+-+-+-+-+-+\n");
		printf("|%c", 'A' + i);
		for (int j = 0; j < 8; j++)
		{
			printf("|%c", board[i][j]);
			(j == 7) ? printf("|") : printf("");
		}
		printf("\n");
	}
	printf("+-+-+-+-+-+-+-+-+-+\n");
}



void checkAlloc(void* ptr, char* msg)
{
	if (ptr == NULL)
	{
		printf("Memory Allocation Failed in: %s", msg);
		exit(1);
	}
}


//This function will print who has the turn and the board after changes.
void printTurn(Board board, Player player, checkersPos src, checkersPos dst)
{
	printf("%c's turn:\n");
	printf("%c%c->%c%c\n", src.row, src.col, dst.row, dst.col);
	//Turn function will be executed here before printing the board.
	printBoard(board);
}