#pragma once
#include "movesTree.h"
#define _CRT_SECURE_NO_WARNINGS


// * Structures * //
typedef struct _SingleSourceMovesListCell
{
	checkersPos* position;
	unsigned short captures;
	struct _SingleSourceMovesListCell* next;

}SingleSourceMovesListCell;

typedef struct _SingleSourceMovesList
{
	SingleSourceMovesListCell* head;
	SingleSourceMovesListCell* tail;
}SingleSourceMovesList;



// ** Function return the height of the tree ** //
int findTreeHeight(SingleSourceMovesTree* moves_tree);
// ** helper tree height ** //
int helperFindTreeHeight(SingleSourceMovesTreeNode* nodeP, int level);
SingleSourceMovesTreeNode* getMaxPos(SingleSourceMovesTree* moves_tree);
// ** helper getMaxPos ** //
void helperGetMaxPos(SingleSourceMovesTreeNode* root, SingleSourceMovesTreeNode** tmpMax, int treeHeight, Player p, bool* isFound);
// ** Function updating the value of the max tree node ** //
void updateMax(Player p, SingleSourceMovesTreeNode*** tmpMax, SingleSourceMovesTreeNode* root);
// ** Function returns list of the best move of player ** //
SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree);
// ** Private case handling. ** //
SingleSourceMovesTreeNode* privateCaseTreeOne(Player p, SingleSourceMovesTree* tr);
// ** Function checks if the next move on the tree of the optimal move is right - return true if so ** //
//bool isPosRight(checkersPos currPos, checkersPos lastPos);


// *** List Functions *** //

// ** Creating Empty List **//
void createEmptyList(SingleSourceMovesList* lst);

// ** Fucntion gets as parameters the data of the new Cell and inserting it to lst end ** //
void insertDataToEndList(SingleSourceMovesList* lst, checkersPos* pos, unsigned short captures, SingleSourceMovesListCell* next);
// ** Function gets list and the new tail of the list and inserting it ** //
void insertCellToEnd(SingleSourceMovesList* lst, SingleSourceMovesListCell* newTail);
// ** Function creates new List Cell ** //
SingleSourceMovesListCell* createNewListCell(checkersPos* pos, unsigned short captures, SingleSourceMovesListCell* next);
// ** Function for debugging the lst ** //
void printList(SingleSourceMovesList* lst);
bool isEmptyList(SingleSourceMovesList* lst);


// test // 
void helperFindSingleSourceOptimalMove(SingleSourceMovesList* res, SingleSourceMovesTreeNode* root, bool* isFound, SingleSourceMovesTreeNode* maxNode);
//int findLenList(SingleSourceMovesList* lst);
void insertToListStart(SingleSourceMovesList* lst, SingleSourceMovesTreeNode root);
