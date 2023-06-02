#pragma once
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS


#define BOARD_SIZE 8	// Size of board

// Casting a char
#define CHARTOROW( X ) ( ( X ) - 65 )	// Casting the Row according to ASCII values
#define CHARTOCOL( X ) ( ( X ) - 49 )	// Casting the Col according to ASCII values

#define LEFT 0		// Left Move Of Player 
#define RIGHT 1		// Right Move Of Player


// Structres 
typedef unsigned char Board[BOARD_SIZE][BOARD_SIZE];

typedef unsigned char Player;

typedef struct _checkersPos
{
	char row, col;
}checkersPos;


// ** Function creates a new Board ** //
void initialBoard(Board board);
// ** Function Checking if there's a checker in certain place on board ** // 
bool isCheckerExist(Board board, checkersPos* pos, Player player);
// ** Function printing current state of the board.
void printBoard(Board board);
// ** Dynamic memory allocation checking function with adjusted message to usr ** // 
void checkAlloc(void* ptr, char* msg);

// ** Function scanning board and counting how many pieces left for player. ** //
int remainingCheckers(Board board, Player player);
