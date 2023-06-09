#include "game.h"
#define NEXT_ARR_SIZE 2



SingleSourceMovesTreeNode* createTreeNode(Board board, checkersPos* currPos,
	unsigned short prevCaps, SingleSourceMovesTreeNode* left, SingleSourceMovesTreeNode* right)
{
	SingleSourceMovesTreeNode* r = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	checkAlloc(r, "Failed TreeNode Allocation!");

	r->pos = currPos; // hasama shel hamikum

	memcpy(r->board, board, 8 * 8 * sizeof(char));//TODO - haklata

	//initial left and right moves to NULL
	r->next_move[LEFT] = left;
	r->next_move[RIGHT] = right;

	r->total_captures_so_far = prevCaps;

	return r;
}

SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src)
{
	bool checkCapsOnly = false;
	int prevCaps = 0;
	bool isMoved = false;
	SingleSourceMovesTree* resTree; //This will be the returned tree.
	Player p;
	
	if (!isCheckerExist(board, src, PLAYER_TOP) && !isCheckerExist(board, src, PLAYER_BOTTOM))
		return NULL;

	else
	{
		resTree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
		checkAlloc(resTree,"Failed Tree Allocation!");
		p = board[CHARTOROW(src->row)][CHARTOCOL(src->col)];
		resTree->source = helper(board, src, prevCaps,checkCapsOnly,p, isMoved);

	}

	return resTree;

}

SingleSourceMovesTreeNode* helper(Board board, checkersPos* currPos,int prevCaps,bool checkCapsOnly,Player p,bool isMoved)
{
	if (currPos == NULL)
		return NULL;

	//create TN
	SingleSourceMovesTreeNode* r;
	Board tmpBoard;
	
	

	//creating a new node
	r = createTreeNode(board, currPos, prevCaps, NULL, NULL);
	
	// here we check for the possible move on the left to our curr location
	checkersPos* posLeft = getNextMove(board, *currPos, LEFT, checkCapsOnly,p, tmpBoard,isMoved);
	
		// There's a possible move to the right
		if (posLeft!=NULL && isMoveCapture(*currPos, *posLeft)) // check if the move is capture move.
		{
			checkCapsOnly = true; // true - it is a capture move
			// Passing to the next iteration the prevCaps incremented by 1 for the capture.
			r->next_move[LEFT] = helper(tmpBoard, posLeft, prevCaps + 1, checkCapsOnly, p, true);
			
		}
		else
			r->next_move[LEFT] = helper(tmpBoard, posLeft, prevCaps, checkCapsOnly, p,true);
		
		if (r->total_captures_so_far == 0 && !isMoved)
		{
			checkCapsOnly = false;
		}

		// here we check for the possible move on the right to our curr location
		checkersPos* posRight = getNextMove(board, *currPos, RIGHT, checkCapsOnly,p, tmpBoard,isMoved);
	
		if (posRight!=NULL && isMoveCapture(*currPos, *posRight))
		{
			checkCapsOnly = true;// true - it is a capture move
			// Passing to the next iteration the prevCaps incremented by 1 for the capture.
			r->next_move[RIGHT] = helper(tmpBoard, posRight, prevCaps + 1, checkCapsOnly, p, true);
		}
		else
			r->next_move[RIGHT] = helper(tmpBoard, posRight, prevCaps, checkCapsOnly, p, true);

	return r;
}


bool isMoveCapture(checkersPos pos1, checkersPos pos2)
{
	if (abs(pos1.col - pos2.col) == 2  && abs(pos1.row - pos2.row) == 2)
		return true;

	return false;
}

bool isOnBoard(int row, int col)
{
	return ((row <= LAST_ROW && row >= FIRST_ROW) && (col <= LAST_COL && col >= FIRST_COL)) ? true : false;
}

checkersPos* getNextMove(Board board, checkersPos pos, int dir, bool isCapture,Player p, Board tmpBoard,bool isMoved)
{
	memcpy(tmpBoard, board, 8 * 8 * sizeof(char));

	checkersPos* nextPos = (checkersPos*)malloc(sizeof(checkersPos));
	checkAlloc(nextPos, "Failed checkersPos Allocation!");
	checkersPos capturedPos;
	capturedPos.col = 0;
	capturedPos.row = 0;
	nextPos->row = 0;
	nextPos->col = 0;

	int currRow = CHARTOROW(pos.row);
	int currCol = CHARTOCOL(pos.col);

	


	switch (dir)
	{
	case LEFT: // check left move
	{
		if (p == PLAYER_TOP)
		{
			if (isCapture) // in capture mode, check only capture moves
			{
				if (isOnBoard(currRow + 1, currCol - 1) && isOnBoard(currRow + 2, currCol - 2) &&
					tmpBoard[currRow + 1][currCol - 1] == PLAYER_BOTTOM && tmpBoard[currRow + 2][currCol - 2] == EMPTY_SQUARE) // can capture left
				{
					//give nextPos this pos and return
					nextPos->row = pos.row + 2;
					nextPos->col = pos.col - 2;
					capturedPos.row = pos.row + 1;
					capturedPos.col = pos.col - 1;
				}
			}
			else // not in capture mode, check all moves
			{
				if(!isMoved)
				{
					if (isOnBoard(currRow + 1, currCol - 1) && tmpBoard[currRow + 1][currCol - 1] == EMPTY_SQUARE)
					{
						//give nextPos this pos and return
						nextPos->row = pos.row + 1;
						nextPos->col = pos.col - 1;
					}

					if (isOnBoard(currRow + 1, currCol - 1) && isOnBoard(currRow + 2, currCol - 2) &&
						tmpBoard[currRow + 1][currCol - 1] == PLAYER_BOTTOM && tmpBoard[currRow + 2][currCol - 2] == EMPTY_SQUARE) // can capture left
					{
						//give nextPos this pos and return
						nextPos->row = pos.row + 2;
						nextPos->col = pos.col - 2;
						capturedPos.row = pos.row + 1;
						capturedPos.col = pos.col - 1;
					}
				}

			}
		}
		else // p==PLAYER_BOTTOM
		{
			if (isCapture) // in capture mode, check only capture moves
			{


				if (isOnBoard(currRow - 1, currCol - 1) && isOnBoard(currRow - 2, currCol - 2) &&
					tmpBoard[currRow - 1][currCol - 1] == PLAYER_TOP && tmpBoard[currRow - 2][currCol - 2] == EMPTY_SQUARE) // can capture left
				{
					//give nextPos this pos and return
					nextPos->row = pos.row - 2;
					nextPos->col = pos.col - 2;
					capturedPos.row = pos.row - 1;
					capturedPos.col = pos.col - 1;
				}

			}
			else // not in capture mode, check all moves
			{
				if(!isMoved)
				{
					if (isOnBoard(currRow - 1, currCol - 1) && tmpBoard[currRow - 1][currCol - 1] == EMPTY_SQUARE)
					{
						//give nextPos this pos and return
						nextPos->row = pos.row - 1;
						nextPos->col = pos.col - 1;
					}

					if (isOnBoard(currRow - 1, currCol - 1) && isOnBoard(currRow - 2, currCol - 2) &&
						tmpBoard[currRow - 1][currCol - 1] == PLAYER_TOP && tmpBoard[currRow - 2][currCol - 2] == EMPTY_SQUARE) // can capture left
					{
						//give nextPos this pos and return
						nextPos->row = pos.row - 2;
						nextPos->col = pos.col - 2;
						capturedPos.row = pos.row - 1;
						capturedPos.col = pos.col - 1;
					}
				}

			}
		}
		break;
	}

	case RIGHT: // check right move
	{
		if (p == PLAYER_TOP)
		{
			if (isCapture) // in capture mode, check only capture moves
			{
				if (isOnBoard(currRow + 1, currCol + 1) && isOnBoard(currRow + 2, currCol + 2) &&
					tmpBoard[currRow + 1][currCol + 1] == PLAYER_BOTTOM && tmpBoard[currRow + 2][currCol + 2] == EMPTY_SQUARE) // can capture left
				{
					//give nextPos this pos and return
					nextPos->row = pos.row + 2;
					nextPos->col = pos.col + 2;
					capturedPos.row = pos.row + 1;
					capturedPos.col = pos.col + 1;
				}
			}
			else // not in capture mode, check all moves
			{
				if(!isMoved)
				{
					if (isOnBoard(currRow + 1, currCol + 1) && tmpBoard[currRow + 1][currCol + 1] == EMPTY_SQUARE)
					{
						//give nextPos this pos and return
						nextPos->row = pos.row + 1;
						nextPos->col = pos.col + 1;
					}

					if (isOnBoard(currRow + 1, currCol + 1) && isOnBoard(currRow + 2, currCol + 2) &&
						tmpBoard[currRow + 1][currCol + 1] == PLAYER_BOTTOM && tmpBoard[currRow + 2][currCol + 2] == EMPTY_SQUARE) // can capture left
					{
						//give nextPos this pos and return
						nextPos->row = pos.row + 2;
						nextPos->col = pos.col + 2;
						capturedPos.row = pos.row + 1;
						capturedPos.col = pos.col + 1;
					}
				}
			}
		}
		else // p==PLAYER_BOTTOM
		{
			if (isCapture) // in capture mode, check only capture moves
			{
				if (isOnBoard(currRow - 1, currCol + 1) && isOnBoard(currRow - 2, currCol + 2) &&
					tmpBoard[currRow - 1][currCol + 1] == PLAYER_TOP && tmpBoard[currRow - 2][currCol + 2] == EMPTY_SQUARE) // can capture left
				{
					//give nextPos this pos and return
					nextPos->row = pos.row - 2;
					nextPos->col = pos.col + 2;
					capturedPos.row = pos.row - 1;
					capturedPos.col = pos.col + 1;
				}
			}
			else // not in capture mode, check all moves
			{
				if(!isMoved)
				{
					if (isOnBoard(currRow - 1, currCol + 1) && tmpBoard[currRow - 1][currCol + 1] == EMPTY_SQUARE)
					{
						//give nextPos this pos and return
						nextPos->row = pos.row - 1;
						nextPos->col = pos.col + 1;
					}

					if (isOnBoard(currRow - 1, currCol + 1) && isOnBoard(currRow - 2, currCol + 2) &&
						tmpBoard[currRow - 1][currCol + 1] == PLAYER_TOP && tmpBoard[currRow - 2][currCol + 2] == EMPTY_SQUARE) // can capture left
					{
						//give nextPos this pos and return
						nextPos->row = pos.row - 2;
						nextPos->col = pos.col + 2;
						capturedPos.row = pos.row - 1;
						capturedPos.col = pos.col + 1;
					}
				}
			}
		}
		break;
	}
	default: break;

	}

	if (nextPos->row != 0 && nextPos->col != 0) // check if player can move
	{
		tmpBoard[CHARTOROW(nextPos->row)][CHARTOCOL(nextPos->col)] = p;
		tmpBoard[currRow][currCol] = EMPTY_SQUARE;
		if (capturedPos.row != 0) // check if player captured
		{
			tmpBoard[CHARTOROW(capturedPos.row)][CHARTOCOL(capturedPos.col)] = EMPTY_SQUARE;
		}

		return nextPos;
	}

	free(nextPos);
	return NULL;
}

void printTree(SingleSourceMovesTree tr)
{
	helperPrint(tr.source);
}

void helperPrint(SingleSourceMovesTreeNode* root)
{
	if (root == NULL)
		return;
	printf("Row: %c , Col: %c ,Cap: %d\n", root->pos->row, root->pos->col, root->total_captures_so_far);
	printBoard(root->board);
	helperPrint(root->next_move[LEFT]);
	helperPrint(root->next_move[RIGHT]);
}

void freeSingleSourceMovesTree(SingleSourceMovesTree* tr)
{
	if (tr)
	{
		freeSingleSourceMovesTreeNode(tr->source);
		free(tr);
	}
}


void freeSingleSourceMovesTreeNode(SingleSourceMovesTreeNode* nodeP)
{
	if (!nodeP->next_move[LEFT] && !nodeP->next_move[RIGHT])
	{
		free(nodeP->pos);
		free(nodeP);
		return;
	}
	else
	{
		if (nodeP->next_move[LEFT])
			freeSingleSourceMovesTreeNode(nodeP->next_move[LEFT]);
		if (nodeP->next_move[RIGHT])
			freeSingleSourceMovesTreeNode(nodeP->next_move[RIGHT]);

		free(nodeP->pos);
		free(nodeP);
		return;
	}
}