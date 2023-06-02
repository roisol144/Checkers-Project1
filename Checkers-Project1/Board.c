#include "game.h"
#include<string.h>

void initialBoard(Board board)
{
	int i, j;
	char player = 'T';

	for (int i = 0; i < 8; i++)
	{
		if (i == 3 || i == 4)
		{
			for (int j = 0; j < 8; j++)
				board[i][j] = ' ';
		}
		else
		{
			if (i % 2 == 0) // row is even
			{
				for (int j = 0; j < 8; j = j + 2)
					board[i][j] = ' ';

				for (int j = 1; j < 8; j = j + 2)
					board[i][j] = player;
			}
			else // row is odd
			{
				for (int j = 0; j < 8; j = j + 2)
					board[i][j] = player;

				for (int j = 1; j < 8; j = j + 2)
					board[i][j] = ' ';
			}
		}

		if (i == 2)
		{
			player = 'B';
		}
	}

	MOVES_T = 0;
	MOVES_B = 0;
	MAX_CAPS = 0;
	MAX_CAPS_PLAYER = 0;
}

bool isCheckerExist(Board board, checkersPos* pos, Player player)
{
	char checker = board[CHARTOROW(pos->row)][CHARTOCOL(pos->col)];

	if (checker != ' ')
	{
		player = checker;
		return true;
	}
	return false;
}

void printBoard(Board board)
{
	int i, j;
	printf("+---+---+---+---+---+---+---+---+---+\n");
	printf("|   | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |\n");
	printf("+---+---+---+---+---+---+---+---+---+\n");
	
	//changing locally the values in cells that 
	// later will be used for statistics.
	char c1, c2, c3, c4;
	c1 = MOVES_T; c2 = MOVES_B; c3 = MAX_CAPS; c4 = MAX_CAPS_PLAYER;
	MOVES_T = EMPTY_SQUARE; MOVES_B = EMPTY_SQUARE; MAX_CAPS = EMPTY_SQUARE; MAX_CAPS_PLAYER = EMPTY_SQUARE;

	for (i = 0; i < BOARD_SIZE; i++)  // ROWS
	{
		printf("| %c ", i + 'A');
		for (j = 0; j < BOARD_SIZE; j++)  // COLS
		{
			printf("| %c ", board[i][j]);
		}
		printf("|\n");
		printf("+---+---+---+---+---+---+---+---+---+\n");
	}
	printf("\n");

	MOVES_T = c1; MOVES_B = c2; MAX_CAPS = c3; MAX_CAPS_PLAYER = c4;
}



void checkAlloc(void* ptr, char* msg)
{
	if (ptr == NULL)
	{
		printf("Memory Allocation Failed in: %s", msg);
		exit(1);
	}
}

int remainingCheckers(Board board, Player player)
{
	int i, j;
	int res = 0;
	for (i = 0; i < BOARD_SIZE; i++)
	{
		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == player)
			{
				res++;
			}
		}
	}
	return res;
}