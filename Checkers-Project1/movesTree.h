#pragma once
#include "Board.h"


// Structures
typedef struct _SingleSourceMovesTreeNode
{
	Board board;
	checkersPos* pos;
	unsigned short total_captures_so_far; // number of caputres
	struct _SingleSourceMovesTreeNode* next_move[2]; // target moves
}SingleSourceMovesTreeNode;

typedef struct _SingleSourceMovesTree
{
	SingleSourceMovesTreeNode* source;

}SingleSourceMovesTree;

checkersPos* getNextMove(Board board, checkersPos pos, int dir, bool isCapture);
bool isMoveCapture(checkersPos pos1, checkersPos pos2);
SingleSourceMovesTreeNode* helper(Board board, checkersPos* currPos, int prevCaps, bool checkCapsOnly);
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src);


