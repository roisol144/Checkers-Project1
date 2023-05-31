#include "game.h"

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

    helperFindSingleSourceOptimalMove(res, root->next_move[LEFT], isFound, maxNode);

    if (*isFound == true)
    {
        insertToListStart(res, *root);
        return;
    }

    helperFindSingleSourceOptimalMove(res, root->next_move[RIGHT], isFound, maxNode);

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

    helperGetMaxPos(root->next_move[LEFT], tmpMax, treeHeight, p, isFound);
    helperGetMaxPos(root->next_move[RIGHT], tmpMax, treeHeight, p, isFound);
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



// ** Possible bug needs attention ** //
// *** Not all control paths return a value *** //


SingleSourceMovesTreeNode* privateCaseTreeOne(Player p, SingleSourceMovesTree* tr)
{
    // in case the tree is only a leaf.
    if (tr->source->next_move[LEFT] == NULL && tr->source->next_move[RIGHT] == NULL)
        return tr->source;

    else if (tr->source->next_move[LEFT] != NULL && tr->source->next_move[RIGHT] != NULL)
    {
        switch (p)
        {
        case PLAYER_TOP:
            if (isMoveCapture(*(tr->source->next_move[RIGHT]->pos), *(tr->source->pos)))
            { // right move is capture - return right move
                return tr->source->next_move[RIGHT];
            }
            else
            {
                if (isMoveCapture(*(tr->source->next_move[LEFT]->pos), *(tr->source->pos)))
                {
                    return tr->source->next_move[LEFT];
                }
                return tr->source->next_move[RIGHT];
            }
        case PLAYER_BOTTOM:
            if (isMoveCapture(*(tr->source->next_move[LEFT]->pos), *(tr->source->pos)))
            { // right move is capture - return right move
                return tr->source->next_move[LEFT];
            }
            else
            {
                if (isMoveCapture(*(tr->source->next_move[RIGHT]->pos), *(tr->source->pos)))
                {
                    return tr->source->next_move[RIGHT];
                }
                return tr->source->next_move[LEFT];
            }

        default:
            break;
        }
    }

    else if (tr->source->next_move[LEFT] != NULL)
    {
        return tr->source->next_move[LEFT];
    }
    else
    {
        return tr->source->next_move[RIGHT];
    }
}


void updateMax(Player p, SingleSourceMovesTreeNode*** tmpMax, SingleSourceMovesTreeNode* root)
{
    switch (p)
    {
    case PLAYER_TOP:
        if ((**tmpMax)->pos->col < root->pos->col)
        {
            **tmpMax = root;
        }
        break;
    case PLAYER_BOTTOM:
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
        leftHeight = helperFindTreeHeight(nodeP->next_move[LEFT], level + 1);
        rightHeight = helperFindTreeHeight(nodeP->next_move[RIGHT], level + 1);
        return 1 + max(leftHeight, rightHeight);
    }
}


MultipleSourceMovesList* FindAllPossiblePlayerMoves(Board board, Player player)
{
    MultipleSourceMovesList* res_lst;
    SingleSourceMovesTree* treeMoves;
    SingleSourceMovesList* listMoves;
    MultipleSourceMovesCell* newCell;
    int i, j;
    checkersPos* pos;
    res_lst = createEmptyListOfLists();
   


    for (i = 0; i < BOARD_SIZE; i++)
    {
        for (j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == player) // if player is the curr.
            {
                pos = createPos(i, j); 
                treeMoves = FindSingleSourceMoves(board, pos);
                listMoves = FindSingleSourceOptimalMove(treeMoves);
                newCell = createListOfListsCell(listMoves);
                insertDataToEndListOfLsts(res_lst, newCell);
                //freeSingleSourceMovesTree(treeMoves);
            }
        }
    }
    return res_lst;
}


checkersPos* createPos(int row, int col)
{
    checkersPos* pos;
    pos = (checkersPos*)malloc(sizeof(checkersPos));  
    checkAlloc(pos, "pos.");                            

    row = row + 65;                                    
    col = col + 49;
    pos->row = (char)row;
    pos->col = (char)col;

    return pos;
}


MultipleSourceMovesList* createEmptyListOfLists()
{
    MultipleSourceMovesList* lst;
    lst = (MultipleSourceMovesList*)malloc(sizeof(MultipleSourceMovesList));
    checkAlloc(lst, "res_lst.");

    lst->head = lst->tail = NULL;
    return lst;
}

MultipleSourceMovesCell* createListOfListsCell(SingleSourceMovesList* lst)
{
    MultipleSourceMovesCell* res_cell = (MultipleSourceMovesCell*)malloc(sizeof(MultipleSourceMovesCell));
    checkAlloc(res_cell, "res_cell");

    res_cell->single_source_moves_list = lst;
    res_cell->next = NULL;

    return res_cell;
}

bool isEmptyListOfLsts(MultipleSourceMovesList* lst)
{
    if (lst->head == NULL)
        return true;

    return false;
}

void insertDataToEndListOfLsts(MultipleSourceMovesList* lst, MultipleSourceMovesCell* newCell)
{

    if (isEmptyListOfLsts(lst))
    {
        lst->head = newCell;
        lst->tail = newCell;
    }
    else
    {
        lst->tail->next = newCell;
        lst->tail = newCell;
    }
}

void freeSingleSourceMovesList(SingleSourceMovesList* lst)
{
    SingleSourceMovesListCell* curr = lst->head;
    SingleSourceMovesListCell* prevCell = NULL;

    while (curr != NULL)
    {
        prevCell = curr;
        curr = curr->next;
        free(prevCell->position);
        free(prevCell);
    }
    free(lst);
}



