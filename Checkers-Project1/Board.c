#include "Board.h"
#include<string.h>

Board* initialBoard()
{
	Board* newBoard = (Board*)calloc(1, sizeof(Board));
	strcpy(newBoard[0], " T T T T");
	strcpy(newBoard[1], "T T T T ");
	strcpy(newBoard[2], " T T T T");
	strcpy(newBoard[3], "        ");
	strcpy(newBoard[4], "        ");
	strcpy(newBoard[5], "B B B B ");
	strcpy(newBoard[6], " B B B B");
	strcpy(newBoard[7], "B B B B ");

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
	for (int i = 0;i < 8;i++)
	{
		printf("%s", board[i]);
		printf("\n");
	}
}
