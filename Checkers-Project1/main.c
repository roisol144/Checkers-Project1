#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"
#include "movesTree.h"
#include "movesList.h"
void printTree(SingleSourceMovesTree tr);
void helperPrint(SingleSourceMovesTreeNode* root);
void main()
{
	/*
					//1	   2    3    4    5    6    7    8
	Board board = { {' ', ' ', ' ', 'T', ' ', ' ', ' ', ' '},//A
					{' ', ' ', ' ', ' ', 'B', ' ', ' ', ' '},//B
					{' ', ' ', ' ', 'T', ' ', ' ', ' ', ' '},//C
					{' ', ' ', 'T', ' ', 'B', ' ', 'B', ' '},//D
					{' ', 'B', ' ', ' ', ' ', 'B', ' ', 'B'},//E
					{'B', ' ', 'B', ' ', ' ', ' ', 'B', ' '},//F
					{' ', 'B', ' ', ' ', ' ', 'B', 'B', 'B'},//G
					{' ', ' ', ' ', ' ', ' ', ' ', ' ', 'B'} };//H
					*/

					//1	   2    3    4    5    6    7    8
	Board board = { {' ', ' ', ' ', 'T', ' ', ' ', ' ', ' '},//A
					{' ', 'T', ' ', ' ', 'B', 'T', ' ', ' '},//B
					{' ', ' ', 'T', 'T', 'T', ' ', ' ', ' '},//C
					{' ', ' ', 'B', ' ', 'B', ' ', ' ', 'T'},//D
					{' ', ' ', 'T', ' ', 'T', 'B', 'T', ' '},//E
					{'B', ' ', 'B', ' ', ' ', ' ', 'B', ' '},//F
					{' ', 'B', 'T', ' ', 'T', 'B', ' ', 'B'},//G
					{' ', ' ', ' ', 'B', ' ', ' ', ' ', ' '} };//H


						//1	   2    3    4    5    6    7    8
	Board fullBoard = { {' ', 'T', ' ', 'T', ' ', 'T', ' ', 'T'},//A
					    {'T', ' ', 'T', ' ', 'T', ' ', 'T', ' '},//B
					    {' ', 'T', ' ', 'T', ' ', 'T', ' ', 'T'},//C
					    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},//D
					    {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},//E
					    {'B', ' ', 'B', ' ', 'B', ' ', 'B', ' '},//F
					    {' ', 'B', ' ', 'B', ' ', 'B', ' ', 'B'},//G
					    {'B', ' ', 'B', ' ', 'B', ' ', 'B', ' '} };//H
					
	//Board* board1 = initialBoard();
	SingleSourceMovesTreeNode* max;
	SingleSourceMovesList* lst;
	printBoard(fullBoard);
	checkersPos temp = { 'F','5' };
	SingleSourceMovesTree tr = *(FindSingleSourceMoves(fullBoard, &temp));
	printTree(tr);
	printf("Height: %d\n", findTreeHeight(&tr));
	max = getMaxPos(&tr);
	printf("MAX: Row: %c, Col: %c \n", max->pos->row, max->pos->col);
	lst = FindSingleSourceOptimalMove(&tr);
	
	printf("\n");

	if (isEmptyList(lst))
		printf("Empty\n");
	else
		printf("Non Empty\n");
		

	printList(lst);
	//dont work on this case because the final pos is left or equal to the original pos
	/*
		//1	   2    3    4    5    6    7    8
	Board board = { {' ', ' ', ' ', 'T', ' ', ' ', ' ', ' '},//A
					{' ', ' ', ' ', ' ', 'B', ' ', ' ', ' '},//B
					{' ', ' ', ' ', 'T', ' ', ' ', ' ', ' '},//C
					{' ', ' ', 'T', ' ', 'B', ' ', ' ', ' '},//D
					{' ', 'B', ' ', ' ', ' ', 'B', ' ', ' '},//E
					{'B', ' ', 'B', ' ', ' ', ' ', 'B', ' '},//F
					{' ', ' ', ' ', ' ', ' ', 'B', 'B', 'B'},//G
					{' ', ' ', ' ', '', ' ', ' ', ' ', 'B'} };//H

					0x00007ff77e2e1fa5 {Checkers-Project1.exe!printf(const char * const _Format, ...), Line 963} {position=...}
	*/	
}


