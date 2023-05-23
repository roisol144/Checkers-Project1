#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"
#include "movesTree.h"
#include "movesList.h"
void printTree(SingleSourceMovesTree tr);
void helperPrint(SingleSourceMovesTreeNode* root);
void main()
{
					//1	   2    3    4    5    6    7    8
	Board board = { {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},//A
					{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},//B
					{' ', ' ', ' ', 'T', ' ', ' ', ' ', ' '},//C
					{' ', ' ', 'B', ' ', 'B', ' ', ' ', ' '},//D
					{' ', 'B', ' ', ' ', ' ', 'B', ' ', ' '},//E
					{'B', ' ', 'B', ' ', ' ', ' ', 'B', ' '},//F
					{' ', 'B', ' ', ' ', ' ', 'B', 'B', 'B'},//G
					{' ', ' ', ' ', ' ', ' ', ' ', ' ', 'B'} };//H
					
	//Board* board1 = initialBoard();
	SingleSourceMovesTreeNode* max;
	SingleSourceMovesList* lst;
	printBoard(board);
	checkersPos temp = { 'C','4' };
	SingleSourceMovesTree tr = *(FindSingleSourceMoves(board, &temp));
	printTree(tr);
	printf("Height: %d\n", findTreeHeight(&tr));
	max = getMaxPos(&tr);
	printf("MAX: Row: %c, Col: %c \n", max->pos->row, max->pos->col);
	lst = FindSingleSourceOptimalMove(&tr);
	printf("\n");
	printList(lst);
	
}


