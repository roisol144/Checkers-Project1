#include "Board.h"
#include "movesTree.h"
#define NEXT_ARR_SIZE 2


SingleSourceMovesTreeNode* createTreeNode(Board board, checkersPos* pos,
	unsigned short total_captures_so_far, SingleSourceMovesTreeNode* next_move[NEXT_ARR_SIZE])
{
	SingleSourceMovesTreeNode* res;
	res = (SingleSourceMovesTreeNode*) malloc(sizeof(SingleSourceMovesTreeNode));
	checkAlloc(res, "New Tree Node Allocation.");
	memcpy(res->board, board, 8*8*sizeof(char));
	res->pos = pos;
	res->total_captures_so_far = total_captures_so_far;

	return res;
}

