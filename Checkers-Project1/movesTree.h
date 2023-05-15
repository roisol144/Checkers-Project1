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

