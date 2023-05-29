#pragma once
#include "Board.h"
#include "movesList.h"
#include "movesTree.h"


void Turn(Board board, Player player);

//void PlayGame(Board board, Player starting_player);

SingleSourceMovesList* getBestMove(MultipleSourceMovesList moves_lst, Player p);

bool comparePositions(checkersPos* resPos, checkersPos* currPos, Player p);