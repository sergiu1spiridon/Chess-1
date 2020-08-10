#ifndef COMMON
#define COMMON

// general use libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {false,true}bool;

typedef struct pieceCoordonate
{
	char piece;
	int x;
	int y;
}pieceCoordonate;


// print the current matrix
void printMatrix(unsigned char** matrix);
// get the difference between the current and initial states
int diffStates(unsigned char**currentMatrix);
// get the total number of pieces in game
int countPieces(unsigned char**currentMatrix);

bool isNotInCheckPlayer(unsigned char**currentMatrix);

bool isNotInCheckAI(unsigned char**currentMatrix);

#endif /* COMMON */