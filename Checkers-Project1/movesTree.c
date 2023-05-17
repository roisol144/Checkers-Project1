#include "Board.h"
#include "movesTree.h"
#define NEXT_ARR_SIZE 2

/*
SingleSourceMovesTreeNode* createTreeNode(Board board, checkersPos* pos,
	unsigned short total_captures_so_far, SingleSourceMovesTreeNode* next_move[])
{
	//Board - 
	SingleSourceMovesTreeNode* res;
	res = (SingleSourceMovesTreeNode*) malloc(sizeof(SingleSourceMovesTreeNode));
	checkAlloc(res, "New Tree Node Allocation.");
	memcpy(res->board, board, 8*8*sizeof(char));
	res->pos = pos;
	res->total_captures_so_far = total_captures_so_far;

	return res;
}
*/

SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src)
{
	bool checkCapsOnly = false;
	int prevCaps = 0;
	SingleSourceMovesTree* resTree; //This will be the returned tree.
	// here possibleMoves function will run
	
	if (!isCheckerExist(board, src, 'T') && !isCheckerExist(board, src, 'B'))
		return NULL;

	else
	{
		resTree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
		resTree->source = helper(board, src, prevCaps,checkCapsOnly);

	}

}

SingleSourceMovesTreeNode* helper(Board board, checkersPos* currPos,int prevCaps,bool checkCapsOnly)
{
	//create TN
	SingleSourceMovesTreeNode* r = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	
	//r->pos = (checkersPos*)malloc(sizeof(checkersPos));
	//*(r->pos) = *currPos;//haataka reduda shel shney charim
	r->pos = currPos;
	memcpy(r->board, board, 8 * 8 * sizeof(char));//TODO - haklata 
	r->next_move[0] = NULL;
	r->next_move[1] = NULL;
	//r->total_captures_so_far = prevCaps;
	//if move illegal this puts NULL;
	checkersPos* posLeft = insertNextMove(board, currPos, true, checkCapsOnly);//true for left
	if (posLeft != NULL)
	{
		//if abs anmudot +-1
	}
		r->next_move[0] = helper(board,posLeft,prevCaps+1);

	checkersPos* posRight = insertNextMove(board, currPos, false, checkCapsOnly);//false for righe
	if (posRight != NULL)
		r->next_move[1] = helper(board, posRight, prevCaps + 1);



}

