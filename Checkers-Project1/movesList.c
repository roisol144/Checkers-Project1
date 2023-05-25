#include "movesList.h"
#include "movesTree.h"
#define ERROR_LVL -1

SingleSourceMovesList* FindSingleSourceOptimalMove(SingleSourceMovesTree* moves_tree)
{
    SingleSourceMovesList* res_lst=(SingleSourceMovesList*)malloc(sizeof(SingleSourceMovesList));
    checkAlloc(res_lst,"list alloc failed");
    createEmptyList(res_lst);
    bool isFound = false;
    // keeping the maxNode is the last node in the optimal branch of the tree
    // that represents the possible moves.
    SingleSourceMovesTreeNode* maxNode = getMaxPos(moves_tree);
    helperFindSingleSourceOptimalMove(res_lst,moves_tree->source,&isFound,maxNode);
    return res_lst;
}

void helperFindSingleSourceOptimalMove(SingleSourceMovesList* res, SingleSourceMovesTreeNode* root,bool* isFound, SingleSourceMovesTreeNode* maxNode)
{
    // if the root does not exist.
    if (root == NULL)
    {
        return;
    }
    // if the desired node in the tree is found.
    if (root == maxNode)
    {
        *isFound = true;
    }

    helperFindSingleSourceOptimalMove(res, root->next_move[0], isFound, maxNode);

    if (*isFound == true)
    {
        insertToListStart(res, *root);
        return;
    }

    helperFindSingleSourceOptimalMove(res, root->next_move[1], isFound, maxNode);

    if (*isFound == true)
    {
        insertToListStart(res, *root);
        return;
    }

}

SingleSourceMovesTreeNode* getMaxPos(SingleSourceMovesTree* moves_tree)
{
    SingleSourceMovesTreeNode* res;
    bool isFound = false;
    int row = CHARTOROW(moves_tree->source->pos->row);
    int col = CHARTOCOL(moves_tree->source->pos->col);
    Player p = moves_tree->source->board[row][col];
    int treeHeight = findTreeHeight(moves_tree);
    if (treeHeight == 0) return moves_tree->source;
    
    if (treeHeight == 1)
        return privateCaseTreeOne(p, moves_tree);

    helperGetMaxPos(moves_tree->source, &res, treeHeight, p, &isFound);
    return res;
}

void helperGetMaxPos(SingleSourceMovesTreeNode* root, SingleSourceMovesTreeNode** tmpMax, int treeHeight, Player p, bool* isFound)
{
    if (root == NULL)
        return;

    helperGetMaxPos(root->next_move[0], tmpMax, treeHeight, p, isFound);
    helperGetMaxPos(root->next_move[1], tmpMax, treeHeight, p, isFound);
    if (!(*isFound) && root->total_captures_so_far == treeHeight)
    {
        *isFound = true;
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


void createEmptyList(SingleSourceMovesList* lst)
{
    lst->head = lst->tail = NULL;
}

int findLenList(SingleSourceMovesList* lst)
{
    SingleSourceMovesListCell* curr = lst->head;
    int res_len = 0;
    if (isEmptyList(lst))
        return 0;
    else
    {
        while (curr != NULL)
        {
            res_len++;
            curr = curr->next;
        }
    }

    return res_len;
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

void insertDataToEndList(SingleSourceMovesList* lst, checkersPos* pos, unsigned short captures, SingleSourceMovesListCell* next)
{
    SingleSourceMovesListCell* newCell;
    newCell = createNewListCell(pos,captures, NULL);
    insertCellToEnd(lst, newCell);

}

void insertToListStart(SingleSourceMovesList* lst, SingleSourceMovesTreeNode root)
{
    SingleSourceMovesListCell* newHead;
    newHead = createNewListCell(root.pos, root.total_captures_so_far, lst->head);
    if (isEmptyList(lst))
    {
        lst->head = newHead;
        lst->tail = newHead;
    }
    else
        lst->head = newHead;
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

