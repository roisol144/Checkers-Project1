#pragma once
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BOARD_SIZE 8
#define _CRT_SECURE_NO_WARNINGS

// Custing a char
#define CHARTOROW( X ) ( ( X ) - 65 )
#define CHARTOCOL( X ) ( ( X ) - 49 )

#define LEFT 0
#define RIGHT 1


// Structres 
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef unsigned char Player;

typedef struct _checkersPos
{
	char row, col;
}checkersPos;


// ** Function creates a new Board ** //
Board* initialBoard();
void initialBoard2(Board board);


// ** Function Checking if there's a checker in certain place on board ** // 
bool isCheckerExist(Board board, checkersPos* pos, Player player);

// ** Function printing current state of the board.
void printBoard(Board board);
// ** Dynamic memory allocation checking function with adjusted message to usr ** // 
void checkAlloc(void* ptr, char* msg);

// ** This function will print the current player who's turn is to play
// and the board after the action the player took ** //
void printTurn(Board board, Player player, checkersPos src, checkersPos dst);

int remainingCheckers(Board board, Player player);
