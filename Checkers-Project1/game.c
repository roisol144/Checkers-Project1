#include "game.h"






void Turn(Board board, Player player)
{
	MultipleSourceMovesList* bestMoves = FindAllPossiblePlayerMoves(board, player);
	SingleSourceMovesList* bestMoveLst = getBestMove(*bestMoves, player);
	SingleSourceMovesListCell* currNode = bestMoveLst->head->next;
	SingleSourceMovesListCell* prevNode = bestMoveLst->head;

	if (currNode->captures == 0)
	{
		board[CHARTOROW(prevNode->position->row)][CHARTOCOL(prevNode->position->col)] = ' ';
		board[CHARTOROW(currNode->position->row)][CHARTOCOL(currNode->position->col)] = player;
	}
	else
	{
		while (currNode != NULL)
		{
			movePlayer(board, player, prevNode->position, currNode->position);
			prevNode = currNode;
			currNode = currNode->next;
		}
	}

}

void movePlayer(Board board, Player p, checkersPos* origin, checkersPos* dest)
{
	int destRow, destCol, orgRow, orgCol;
	destRow = CHARTOROW(dest->row);
	destCol = CHARTOCOL(dest->col);
	orgRow = CHARTOROW(origin->row);
	orgCol = CHARTOCOL(origin->col);

	board[orgRow][orgCol] = ' ';
	board[destRow][destCol] = p;

	switch (p)
	{
		case 'T':
		{
			if (destCol > orgCol) // right capture
			{
				board[orgRow + 1][orgCol + 1] = ' ';
			}
			else // left move
			{
				board[orgRow + 1][orgCol - 1] = ' ';
			}
			break;
		}
		case 'B':
		{
			if (destCol > orgCol) // right capture
			{
				board[orgRow - 1][orgCol + 1] = ' ';
			}
			else // left move
			{
				board[orgRow - 1][orgCol - 1] = ' ';
			}
			break;
		}
	default:
		break;
	}
	
}

SingleSourceMovesList* getBestMove(MultipleSourceMovesList moves_lst,Player p)
{
	SingleSourceMovesList* res_lst;
	MultipleSourceMovesCell* curr_lst;

	/*captures of the first optimal move*/
	int maxCaptures = moves_lst.head->single_source_moves_list->tail->captures;;
	int currCaps;
	checkersPos* resPos;
	checkersPos* currPos;

	/*initialize variable to first move*/
	res_lst = moves_lst.head->single_source_moves_list;
	curr_lst = moves_lst.head->next;
	
	while (curr_lst != NULL)
	{
		currCaps = curr_lst->single_source_moves_list->tail->captures;
		if (currCaps > maxCaptures)
		{
			res_lst = curr_lst->single_source_moves_list;
		}
		if (currCaps == maxCaptures)
		{
			/*send resLst and currLst and compare poses of the roots*/
			/*if function return true - swap*/
			resPos = res_lst->head->position;
			currPos = curr_lst->single_source_moves_list->head->position;

			if (comparePositions(resPos, currPos,p))
			{
				res_lst = curr_lst->single_source_moves_list;
			}
		}

		curr_lst = curr_lst->next;
	}

	return res_lst;
}


bool comparePositions(checkersPos* resPos, checkersPos* currPos,Player p)
{
	int resRow, resCol, currRow, currCol;
	resRow = resPos->row;
	resCol = resPos->col;
	currRow = currPos->row;
	currCol = currPos->col;

	bool resBool = false;

	switch (p)
	{
		case 'T':
		{
			if (currRow > resRow)
			{
				resBool = true;
			}

			if (currRow == resRow && currCol > resCol)
			{
				resBool = true;
			}

			break;
		}
		case 'B':
		{
			if (currRow < resRow)
			{
				resBool = true;
			}

			if (currRow == resRow && currCol < resCol)
			{
				resBool = true;
			}

			break;
		}
	default:
		break;
	}

	return resBool;
}




//void PlayGame(Board board, Player starting_player);