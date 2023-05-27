#pragma once
#include "Board.h"
#include <math.h>



// ** Structures ** //
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


// ** The function will return the an object (checkersPos type) representing the next position of the checker ** //
checkersPos* getNextMove(Board board, checkersPos pos, int dir, bool isCapture, Player p, Board tmpBoard, bool isMoved);


// ** The function will check if the last move was capture move or not ** //
bool isMoveCapture(checkersPos pos1, checkersPos pos2);

// ** The function will return a pointer to the tree of possible moves for a specific checker on board. ** //
SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src);

// ** The function is the helper function of FindSingleSourceMoves - recursion occurs here. ** // 
SingleSourceMovesTreeNode* helper(Board board, checkersPos* currPos, int prevCaps, bool checkCapsOnly, Player p, bool isMoved);

SingleSourceMovesTreeNode* createTreeNode(Board board, checkersPos* currPos,
	unsigned short prevCaps, SingleSourceMovesTreeNode* left, SingleSourceMovesTreeNode* right);


// ** The function will check if the position is valid - on board. ** //
bool isOnBoard(int row, int col);


//** print tree ** //
void printTree(SingleSourceMovesTree tr);
void helperPrint(SingleSourceMovesTreeNode* root);


// ** free **//

void freeSingleSourceMovesTree(SingleSourceMovesTree* tr);
void freeSingleSourceMovesTreeNode(SingleSourceMovesTreeNode* nodeP);

