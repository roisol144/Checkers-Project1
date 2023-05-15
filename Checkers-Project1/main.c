#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"

void main()
{
	Board* board1 = initialBoard();
	Board board2;
	memcpy(board2, *board1, 8 * 8 * sizeof(char));
	printBoard(board2);
}
