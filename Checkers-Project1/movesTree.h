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

//This function will check the allocation of an object
void checkAlloc(void* ptr, char* msg);