#include "movesList.h"
#include "movesTree.h"
#define ERROR_LVL -1


SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
	SingleSourceMovesList* res_lst;
    //SingleSourceMovesListCell* currCell;
    SingleSourceMovesTreeNode* currTreeNode;
    SingleSourceMovesTreeNode* lstTail = getMaxPos(moves_tree); // returns the final Tree node that will be the the tail of the returned list.
   // SingleSourceMovesListCell* newTail = createNewListCell(lstTail->pos, lstTail->total_captures_so_far, NULL); // converting tree node to lst node.
    //int treeHeight = findTreeHeight(moves_tree);
    //checkalloc
    res_lst = (SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
    createEmptyList(res_lst);
    checkAlloc(res_lst, "return list of optimal move.\n");

    // No possible move. 
    if (moves_tree->source == NULL)
        return NULL;

    currTreeNode = moves_tree->source;
    
    while (currTreeNode != lstTail)
    {
        // inserting the current "root" to the lst.
        insertDataToEndList(res_lst, currTreeNode->pos, currTreeNode->total_captures_so_far, NULL);

        // checking if the next Tree Node is to the right
        if (isPosRight(*(currTreeNode->pos),*(lstTail->pos)))
        {
            //go to the right node
            currTreeNode = currTreeNode->next_move[1];
        }
        else
        {
            //go to the left node
            currTreeNode = currTreeNode->next_move[0];
        }
    }
    
    // inserting the last node in the tree.
    insertDataToEndList(res_lst, lstTail->pos, lstTail->total_captures_so_far, NULL);

	return res_lst;
}

bool isPosRight(checkersPos currPos, checkersPos lastPos)
{
    if (CHARTOCOL(currPos.col) < CHARTOCOL(lastPos.col)) // right
    {
        return true;
    }
    else // left
    {
        return false;
    }
}

SingleSourceMovesTreeNode* getMaxPos(SingleSourceMovesTree* moves_tree)
{
    SingleSourceMovesTreeNode* res;
    int row = CHARTOROW(moves_tree->source->pos->row);
    int col = CHARTOCOL(moves_tree->source->pos->col);
    Player p = moves_tree->source->board[row][col];
    int treeHeight = findTreeHeight(moves_tree);
    if (treeHeight == 0) return moves_tree->source;
    
    if (treeHeight == 1)
        return privateCaseTreeOne(p, moves_tree);

    helperGetMaxPos(moves_tree->source, &res, treeHeight, p, false);
    return res;
}

void helperGetMaxPos(SingleSourceMovesTreeNode* root, SingleSourceMovesTreeNode** tmpMax, int treeHeight, Player p, bool isFound)
{
    if (root == NULL)
        return;

    helperGetMaxPos(root->next_move[0], tmpMax, treeHeight, p, isFound);
    helperGetMaxPos(root->next_move[1], tmpMax, treeHeight, p, isFound);
    if (!isFound && root->total_captures_so_far == treeHeight)
    {
        isFound = true;
        *tmpMax = root;
    }

    else if (root->total_captures_so_far == treeHeight) // if we've reached the height of the tree and isFound = true
    {
        updateMax(p, &tmpMax, root);
    }
}


SingleSourceMovesTreeNode* privateCaseTreeOne(Player p, SingleSourceMovesTree* tr)
{
    // in case the tree is only a leaf.
    if (tr->source->next_move[0] == NULL && tr->source->next_move[1] == NULL)
        return tr->source;

    else if (tr->source->next_move[0] != NULL && tr->source->next_move[1] != NULL)
    {
        switch (p)
        {
        case 'T':
            if (isMoveCapture(*(tr->source->next_move[1]->pos), *(tr->source->pos)))
            { // right move is capture - return right move
                return tr->source->next_move[1];
            }
            else
            {
                if (isMoveCapture(*(tr->source->next_move[0]->pos), *(tr->source->pos)))
                {
                    return tr->source->next_move[0];
                }
                return tr->source->next_move[1];
            }
        case 'B':
            if (isMoveCapture(*(tr->source->next_move[0]->pos), *(tr->source->pos)))
            { // right move is capture - return right move
                return tr->source->next_move[0];
            }
            else
            {
                if (isMoveCapture(*(tr->source->next_move[1]->pos), *(tr->source->pos)))
                {
                    return tr->source->next_move[1];
                }
                return tr->source->next_move[0];
            }

        default:
            break;
        }
    }

    else if (tr->source->next_move[0] != NULL)
    {
        return tr->source->next_move[0];
    }
    else
    {
        return tr->source->next_move[1];
    }
}


void updateMax(Player p, SingleSourceMovesTreeNode*** tmpMax, SingleSourceMovesTreeNode* root)
{
    switch (p)
    {
    case 'T':
        if ((**tmpMax)->pos->col < root->pos->col)
        {
            **tmpMax = root;
        }
        break;
    case 'B':
        if ((**tmpMax)->pos->col > root->pos->col)
        {
            **tmpMax = root;
        }
        break;
    default:
        break;
    }
}


SingleSourceMovesList* createEmptyList(SingleSourceMovesList* lst)
{
    lst->head = lst->tail = NULL;
}

SingleSourceMovesListCell* createNewListCell(checkersPos* pos, unsigned short captures, SingleSourceMovesListCell* next)
{
    SingleSourceMovesListCell* newCell;
    newCell = (SingleSourceMovesListCell*)malloc(sizeof(SingleSourceMovesListCell));
    checkAlloc(newCell, "New List Cell.\n");
    
    newCell->captures = captures;
    newCell->position = pos;
    newCell->next = next;

    return newCell;
}

void printList(SingleSourceMovesList* lst)
{
    SingleSourceMovesListCell* curr = lst->head;
    while (curr != NULL)
    {
        printf("Pos:%c%c -> ", curr->position->row, curr->position->col);
        curr = curr->next;
    }
}

bool isEmptyList(SingleSourceMovesList* lst)
{
    if (lst->head == NULL)
        return true;
    return false;
}
/*
void insertDataToEndList(SingleSourceMovesTree* moves_tree, SingleSourceMovesList* lst,checkersPos* pos, unsigned short captures, SingleSourceMovesListCell* next)
{
    SingleSourceMovesListCell* newCell;
    newCell = createNewListCell(moves_tree->source->pos, moves_tree->source->total_captures_so_far, NULL);
    insertCellToEnd(lst, newCell);

}*/

void insertDataToEndList(SingleSourceMovesList* lst, checkersPos* pos, unsigned short captures, SingleSourceMovesListCell* next)
{
    SingleSourceMovesListCell* newCell;
    newCell = createNewListCell(pos,captures, NULL);
    insertCellToEnd(lst, newCell);

}

void insertCellToEnd(SingleSourceMovesList* lst, SingleSourceMovesListCell* newTail)
{
    if (isEmptyList(lst))
    {
        lst->head = newTail;
        lst->tail = newTail;
    }
    else
    {
        lst->tail->next = newTail;
        lst->tail = newTail;
    }   
}


int findTreeHeight(SingleSourceMovesTree* moves_tree)
{
    return helperFindTreeHeight(moves_tree->source, 0);
}

int helperFindTreeHeight(SingleSourceMovesTreeNode* nodeP, int level)
{
    int leftHeight, rightHeight;
    if (nodeP == NULL)
        return ERROR_LVL;
    else
    {
        leftHeight = helperFindTreeHeight(nodeP->next_move[0], level + 1);
        rightHeight = helperFindTreeHeight(nodeP->next_move[1], level + 1);
        return 1 + max(leftHeight, rightHeight);
    }
}

