#include "Board.h"
#include "movesTree.h"
#define NEXT_ARR_SIZE 2
#define LEFT 0
#define RIGHT 1


SingleSourceMovesTreeNode* createTreeNode(Board board, checkersPos* currPos,
	unsigned short prevCaps, SingleSourceMovesTreeNode* left, SingleSourceMovesTreeNode* right)
{
	SingleSourceMovesTreeNode* r = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	checkAlloc(r, "Failed TreeNode Allocation!");

	r->pos = currPos; // hasama shel hamikum

	memcpy(r->board, board, 8 * 8 * sizeof(char));//TODO - haklata

	//initial left and right moves to NULL
	r->next_move[0] = left;
	r->next_move[1] = right;

	r->total_captures_so_far = prevCaps;

	return r;
}

SingleSourceMovesTree* FindSingleSourceMoves(Board board, checkersPos* src)
{
	bool checkCapsOnly = false;
	int prevCaps = 0;
	SingleSourceMovesTree* resTree; //This will be the returned tree.
	Player p;
	
	if (!isCheckerExist(board, src, 'T') && !isCheckerExist(board, src, 'B'))
		return NULL;

	else
	{
		resTree = (SingleSourceMovesTree*)malloc(sizeof(SingleSourceMovesTree));
		checkAlloc(resTree,"Failed Tree Allocation!");
		p = board[CHARTOROW(src->row)][CHARTOCOL(src->col)];
		resTree->source = helper(board, src, prevCaps,checkCapsOnly,p);

	}

	return resTree;

}

SingleSourceMovesTreeNode* helper(Board board, checkersPos* currPos,int prevCaps,bool checkCapsOnly,Player p)
{
	if (currPos == NULL)
		return NULL;

	//create TN
	SingleSourceMovesTreeNode* r = (SingleSourceMovesTreeNode*)malloc(sizeof(SingleSourceMovesTreeNode));
	checkAlloc(r, "Failed TreeNode Allocation!");

	
//	r->pos = currPos; // hasama shel hamikum

//	memcpy(r->board, board, 8 * 8 * sizeof(char));//TODO - haklata 

	//initial left and right moves to NULL
//	r->next_move[0] = NULL;
//	r->next_move[1] = NULL;

//	r->total_captures_so_far = prevCaps;

	//creating a new node
	r = createTreeNode(board, currPos, prevCaps, checkCapsOnly, NULL, NULL);
	
	// here we check for the possible move on the left to our curr location
	checkersPos* posLeft = getNextMove(board, *currPos, LEFT, checkCapsOnly,p);
	if (posLeft != NULL)
	{
		// There's a possible move to the right
		if (isMoveCapture(*currPos, *posLeft)) // check if the move is capture move.
		{
			checkCapsOnly = true; // true - it is a capture move
			// Passing to the next iteration the prevCaps incremented by 1 for the capture.
			r->next_move[0] = helper(board, posLeft, prevCaps + 1, checkCapsOnly, p);
		}
		else
		{
			r->next_move[0] = helper(board, posLeft, prevCaps, checkCapsOnly, p);
		}
	}
	else
	{
		r->next_move[0] = helper(board, NULL, prevCaps, checkCapsOnly, p);
	}
	
	if (board[CHARTOROW(currPos->row)][CHARTOCOL(currPos->col)] == p)
	{
		checkCapsOnly = false;
	}

	// here we check for the possible move on the right to our curr location
	checkersPos* posRight = getNextMove(board, *currPos, RIGHT, checkCapsOnly,p);
	if (posRight != NULL)
	{
		if (isMoveCapture(*currPos, *posRight))
		{
			checkCapsOnly = true;// true - it is a capture move
			// Passing to the next iteration the prevCaps incremented by 1 for the capture.
			r->next_move[1] = helper(board, posRight, prevCaps + 1, checkCapsOnly, p);
		}
		else
			r->next_move[1] = helper(board, posRight, prevCaps, checkCapsOnly, p);
	}
	else
	{
		r->next_move[1] = helper(board, NULL, prevCaps, checkCapsOnly, p);
	}
	
	
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
	return ((row <= 7 && row >= 0) && (col <= 7 && col >= 0)) ? true : false;
}

checkersPos* getNextMove(Board board, checkersPos pos, int dir, bool isCapture,Player p)
{
	checkersPos* nextPos = (checkersPos*)malloc(sizeof(checkersPos));
	checkAlloc(nextPos, "Failed checkersPos Allocation!");
	nextPos->row = 0;
	nextPos->col = 0;

	int currRow = CHARTOROW(pos.row);
	int currCol = CHARTOCOL(pos.col);

	


	switch (dir)
	{
	case LEFT: // check left move
	{
		if (p == 'T')
		{
			if (isCapture) // in capture mode, check only capture moves
			{


				if (isOnBoard(currRow + 1, currCol - 1) && isOnBoard(currRow + 2, currCol - 2) &&
					board[currRow + 1][currCol - 1] == 'B' && board[currRow + 2][currCol - 2] == ' ') // can capture left
				{
					//give nextPos this pos and return
					nextPos->row = pos.row + 2;
					nextPos->col = pos.col - 2;
				}

			}
			else // not in capture mode, check all moves
			{
				if (isOnBoard(currRow + 1, currCol - 1) && board[currRow + 1][currCol - 1] == ' ')
				{
					//give nextPos this pos and return
					nextPos->row = pos.row + 1;
					nextPos->col = pos.col - 1;
				}

				if (isOnBoard(currRow + 1, currCol - 1) && isOnBoard(currRow + 2, currCol - 2) &&
					board[currRow + 1][currCol - 1] == 'B' && board[currRow + 2][currCol - 2] == ' ') // can capture left
				{
					//give nextPos this pos and return
					nextPos->row = pos.row + 2;
					nextPos->col = pos.col - 2;
				}

			}
		}
		else // p=='B'
		{
			if (isCapture) // in capture mode, check only capture moves
			{


				if (isOnBoard(currRow - 1, currCol - 1) && isOnBoard(currRow - 2, currCol - 2) &&
					board[currRow - 1][currCol - 1] == 'T' && board[currRow - 2][currCol - 2] == ' ') // can capture left
				{
					//give nextPos this pos and return
					nextPos->row = pos.row - 2;
					nextPos->col = pos.col - 2;
				}

			}
			else // not in capture mode, check all moves
			{
				if (isOnBoard(currRow - 1, currCol - 1) && board[currRow - 1][currCol - 1] == ' ')
				{
					//give nextPos this pos and return
					nextPos->row = pos.row - 1;
					nextPos->col = pos.col - 1;
				}

				if (isOnBoard(currRow - 1, currCol - 1) && isOnBoard(currRow - 2, currCol - 2) &&
					board[currRow - 1][currCol - 1] == 'T' && board[currRow - 2][currCol - 2] == ' ') // can capture left
				{
					//give nextPos this pos and return
					nextPos->row = pos.row - 2;
					nextPos->col = pos.col - 2;
				}

			}
		}
		break;
	}

	case RIGHT: // check right move
	{
		if (p == 'T')
		{
			if (isCapture) // in capture mode, check only capture moves
			{
				if (isOnBoard(currRow + 1, currCol + 1) && isOnBoard(currRow + 2, currCol + 2) &&
					board[currRow + 1][currCol + 1] == 'B' && board[currRow + 2][currCol + 2] == ' ') // can capture left
				{
					//give nextPos this pos and return
					nextPos->row = pos.row + 2;
					nextPos->col = pos.col + 2;
				}
			}
			else // not in capture mode, check all moves
			{
				if (isOnBoard(currRow + 1, currCol + 1) && board[currRow + 1][currCol + 1] == ' ')
				{
					//give nextPos this pos and return
					nextPos->row = pos.row + 1;
					nextPos->col = pos.col + 1;
				}

				if (isOnBoard(currRow + 1, currCol + 1) && isOnBoard(currRow + 2, currCol + 2) &&
					board[currRow + 1][currCol + 1] == 'B' && board[currRow + 2][currCol + 2] == ' ') // can capture left
				{
					//give nextPos this pos and return
					nextPos->row = pos.row + 2;
					nextPos->col = pos.col + 2;
				}
			}
		}
		else // p=='B'
		{
			if (isCapture) // in capture mode, check only capture moves
			{
				if (isOnBoard(currRow - 1, currCol + 1) && isOnBoard(currRow - 2, currCol + 2) &&
					board[currRow - 1][currCol + 1] == 'T' && board[currRow - 2][currCol + 2] == ' ') // can capture left
				{
					//give nextPos this pos and return
					nextPos->row = pos.row - 2;
					nextPos->col = pos.col + 2;
				}
			}
			else // not in capture mode, check all moves
			{
				if (isOnBoard(currRow - 1, currCol + 1) && board[currRow - 1][currCol + 1] == ' ')
				{
					//give nextPos this pos and return
					nextPos->row = pos.row - 1;
					nextPos->col = pos.col + 1;
				}

				if (isOnBoard(currRow - 1, currCol + 1) && isOnBoard(currRow - 2, currCol + 2) &&
					board[currRow - 1][currCol + 1] == 'T' && board[currRow - 2][currCol + 2] == ' ') // can capture left
				{
					//give nextPos this pos and return
					nextPos->row = pos.row - 2;
					nextPos->col = pos.col + 2;
				}
			}
		}
		break;
	}
	default: break;

	}

	if (nextPos->row != 0 && nextPos->col != 0)
		return nextPos;

	free(nextPos);
	return NULL;
}


