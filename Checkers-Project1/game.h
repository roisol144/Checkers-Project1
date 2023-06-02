#pragma once
#include "Board.h"
#include "movesList.h"
#include "movesTree.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define PLAYER_TOP 'T'		// Player that plays from Top -> Bottom
#define PLAYER_BOTTOM 'B'	// Player that plays from Bottom -> Top
#define EMPTY_SQUARE ' '	// Empty Cell
#define FIRST_ROW 0		// First Row On Board
#define FIRST_COL 0		// First Col On Board
#define LAST_ROW 7		// Last Row On Board
#define LAST_COL 7		// Last Col On Board
#define MOVES_T board[2][0]		// Number Of Moves Player T
#define MOVES_B board[2][2]		// Number Of Moves Player B
#define MAX_CAPS board[2][4]	// Number Of Max Captures In Single Turn
#define MAX_CAPS_PLAYER board[2][6]		// Char Of Player With Most Consequitive Captures			




// ** Function perform the best move of player ** //
void Turn(Board board, Player player);
// ** Function switch the turns ** //
Player changePlayerTurn(Player current);
// ** Function checking if the game is over or not ** //
bool gameOver(Board board, Player player);
//** Function priniting game statistics and the winner ** //
void gameOverMSG(Board board, Player player);
// ** function controling the game ** // 
void PlayGame(Board board, Player starting_player);
// ** function retunring a list which representing the best move of player p ** //
SingleSourceMovesList* getBestMove(MultipleSourceMovesList moves_lst, Player p);
// ** function changing the board according to the move ** //
void movePlayer(Board board, Player p, checkersPos* origin, checkersPos* dest);
// **Function checking where to move accodring to game restrictions ** //
bool comparePositions(checkersPos* resPos, checkersPos* currPos, Player p);