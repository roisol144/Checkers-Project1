#pragma once
#include "game.h"
#include "movesList.h"
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

typedef struct _multipleSourceMovesListCell
{
	SingleSourceMovesList* single_source_moves_list;
	struct _multipleSourceMovesListCell* next;

}MultipleSourceMovesCell;

typedef struct _multipleSourceMovesList
{
	MultipleSourceMovesCell* head;
	MultipleSourceMovesCell* tail;
}MultipleSourceMovesList;





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
// ** Helper for FindSingleSourceOptimalMove **//
void helperFindSingleSourceOptimalMove(SingleSourceMovesList* res, SingleSourceMovesTreeNode* root, bool* isFound, SingleSourceMovesTreeNode* maxNode);
// ** Private case handling. ** //
SingleSourceMovesTreeNode* privateCaseTreeOne(Player p, SingleSourceMovesTree* tr);

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
// ** Function Checking if the list of type SingleSourceMovesList ** //
bool isEmptyList(SingleSourceMovesList* lst);
// ** Function returning the length if list of type SingleSourceMovesList ** //
int findLenList(SingleSourceMovesList* lst);
// ** function inserting to list start a node of a tree after moving its data to suitable type ** //
void insertToListStart(SingleSourceMovesList* lst, SingleSourceMovesTreeNode root);


// ** Function return multipleList of player's best moves of every piece ** //
MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player);
// ** Function check if a given list of type MultipleSourceMovesList is empty ** //
bool isEmptyListOfLsts(MultipleSourceMovesList* lst);
// ** Function creating An Empty List Of Type MultipleSourceMovesList **//
MultipleSourceMovesList* createEmptyListOfLists();
// ** Function inserting newCell of type MultipleSourceMovesCell to list of type MultipleSourceMovesList ** //
void insertDataToEndListOfLsts(MultipleSourceMovesList* lst, MultipleSourceMovesCell* newCell);
// ** Function Creates a new pos and mallocing it ** //
checkersPos* createPos(int row, int col);
// ** Function Creates A List Cell ** //
MultipleSourceMovesCell* createListOfListsCell(SingleSourceMovesList* lst);

// ** free ** //
void freeSingleSourceMovesList(SingleSourceMovesList* lst);
void freeMultipulSourceMovesList(MultipleSourceMovesList* lst);

