#include "Board.h"
#include "movesTree.h"
#define NEXT_ARR_SIZE 2
#define LEFT 0
#define RIGHT 1

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
	
	if (!isCheckerExist(board, src, 'T') && !isCheckerExist(board, src, 'B'))
		return NULL;

	else
	{
		resTree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
		checkAlloc(resTree,"Failed Tree Allocation!");
		resTree->source = helper(board, src, prevCaps,checkCapsOnly);

	}

}

SingleSourceMovesTreeNode* helper(Board board, checkersPos* currPos,int prevCaps,bool checkCapsOnly)
{
	//create TN
	SingleSourceMovesTreeNode* r = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	checkAlloc(r, "Failed TreeNode Allocation!");

	
	r->pos = currPos; // hasama shel hamikum

	memcpy(r->board, board, 8 * 8 * sizeof(char));//TODO - haklata 

	//initial left and right moves to NULL
	r->next_move[0] = NULL;
	r->next_move[1] = NULL;

	r->total_captures_so_far = prevCaps;
	
	//if move illegal this puts NULL;
	checkersPos* posLeft = getNextMove(board, *currPos, LEFT, checkCapsOnly);//true for left
	if (posLeft != NULL)
	{
		if (isMoveCapture(*currPos,*posLeft))//TODO isMoveCapture
		{
			checkCapsOnly = true;
			r->next_move[0] = helper(board, posLeft, prevCaps + 1, checkCapsOnly);
		}
		else
		{
			r->next_move[0] = helper(board, posLeft, prevCaps, checkCapsOnly);
		}
	}
		

	checkersPos* posRight = getNextMove(board, *currPos, RIGHT, checkCapsOnly);//false for righe
	if (posRight != NULL)
	{
		if (isMoveCapture(*currPos, *posRight))//TODO isMoveCapture
		{
			checkCapsOnly = true;
			r->next_move[1] = helper(board, posRight, prevCaps + 1, checkCapsOnly);
		}
		else
		{
			r->next_move[1] = helper(board, posRight, prevCaps, checkCapsOnly);
		}
	}
	


}

bool isMoveCapture(checkersPos pos1, checkersPos pos2)
{

}

checkersPos* getNextMove(Board board,checkersPos pos,int dir,bool isCapture)
{

}

