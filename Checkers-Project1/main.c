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
	MultipleSourceMovesList* all_posibble_moves;
	MultipleSourceMovesCell* curr;
//	printBoard(board);
	checkersPos temp = { 'A','4' };
	SingleSourceMovesTree tr = *(FindSingleSourceMoves(board, &temp));
	printTree(tr);
	printf("Height: %d\n", findTreeHeight(&tr));
	max = getMaxPos(&tr);
	printf("MAX: Row: %c, Col: %c \n", max->pos->row, max->pos->col);
	lst = FindSingleSourceOptimalMove(&tr);
	printf("\n");
	//printList(lst);	
	printf("\n");
	all_posibble_moves = FindAllPossiblePlayerMoves(board, 'T');
	curr = all_posibble_moves->head;
	
	while (curr != NULL)
	{
		printList(curr->single_source_moves_list);
		printf("\n");
		curr = curr->next;
	}



}


