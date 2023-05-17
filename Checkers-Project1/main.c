#define _CRT_SECURE_NO_WARNINGS
#include "Board.h"
#include "movesTree.h"
void printTree(SingleSourceMovesTree tr);
void helperPrint(SingleSourceMovesTreeNode* root);
void main()
{
	Board* board1 = initialBoard();
	printBoard(*board1);
	checkersPos temp = { 'D','4' };
	SingleSourceMovesTree tr = *(FindSingleSourceMoves(*board1, &temp));
	printTree(tr);
	
}

void printTree(SingleSourceMovesTree tr)
{
	helperPrint(tr.source);
}

void helperPrint(SingleSourceMovesTreeNode* root)
{
	if (root == NULL)
		return;
	printf("%c %c\n", root->pos->row, root->pos->col);
	helperPrint(root->next_move[0]);
	helperPrint(root->next_move[1]);
}
