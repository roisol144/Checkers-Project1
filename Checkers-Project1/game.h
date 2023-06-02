#pragma once
#include "Board.h"
#include "movesList.h"
#include "movesTree.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define PLAYER_TOP 'T'
#define PLAYER_BOTTOM 'B'
#define EMPTY_SQUARE ' '
#define FIRST_ROW 0
#define FIRST_COL 0
#define LAST_ROW 7
#define LAST_COL 7
#define MOVES_T board[2][0]
#define MOVES_B board[2][2]
#define MAX_CAPS board[2][4]
#define MAX_CAPS_PLAYER board[2][6]





void Turn(Board board, Player player);
Player changePlayerTurn(Player current);
bool gameOver(Board board, Player player);
void gameOverMSG(Board board, Player player);

void PlayGame(Board board, Player starting_player);

SingleSourceMovesList* getBestMove(MultipleSourceMovesList moves_lst, Player p);
void movePlayer(Board board, Player p, checkersPos* origin, checkersPos* dest);

bool comparePositions(checkersPos* resPos, checkersPos* currPos, Player p);