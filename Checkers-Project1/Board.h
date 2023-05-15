#pragma once
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BOARD_SIZE 8
#define _CRT_SECURE_NO_WARNINGS

#define CHARTOROW( X ) ( ( X ) - 64 )
#define CHARTOCOL( X ) ( ( X ) - 48 )

typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef unsigned char Player;

typedef struct _checkersPos
{
	char row, col;
}checkersPos;


Board* initialBoard();
bool isCheckerExist(Board board, checkersPos* pos, Player* player);
void printBoard(Board board);