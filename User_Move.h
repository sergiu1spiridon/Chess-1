#ifndef USER_MOVE
#define USER_MOVE

// general use libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game_Logic.h"

typedef struct pieceCoordonate
{
	char piece;
	int x;
	int y;
}pieceCoordonate;

void printMatrix(unsigned char** matrix);

int validPion(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		pieceCoordonate *pieceToMove);

int validPionAttack(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		pieceCoordonate *pieceToMove);

int validKnight(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		pieceCoordonate *pieceToMove);

int validRook(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		pieceCoordonate *pieceToMove);

int validBishop(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		pieceCoordonate *pieceToMove);

int validMove(unsigned char **currentMatrix,pieceCoordonate *pieceToMove);

unsigned char* getPlayerMove(unsigned char* currentKey);

#endif/*USER_MOVE*/