#include "game.h"
#include<string.h>


/*
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
	(*newBoard)[0][1] = 0;
	(*newBoard)[0][3] = 0;
	(*newBoard)[0][5] = 0;
	(*newBoard)[0][7] = 0;


	return newBoard;
}
*/

void initialBoard2(Board board)
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


// ** Debug Board Exp. ** // 
/*
Board board = { {' ', 'T', ' ', 'T', ' ', 'T', ' ', 'T'},
				{'T', ' ', 'T', ' ', 'T', ' ', 'T', ' '},
				{' ', 'T', ' ', 'T', ' ', 'T', ' ', 'T'},
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
				{'B', ' ', 'B', ' ', 'B', ' ', 'B', ' '},
				{' ', 'B', ' ', 'B', ' ', 'B', ' ', 'B'},
				{'B', ' ', 'B', ' ', 'B', ' ', 'B', ' '}};
*/

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
/*
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
*/

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


void printTurn(Board board, Player player, checkersPos src, checkersPos dst)
{
	printf("%c's turn:\n", player);
	printf("%c%c->%c%c\n", src.row, src.col, dst.row, dst.col);
	//Turn function will be executed here before printing the board.
	printBoard(board);
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