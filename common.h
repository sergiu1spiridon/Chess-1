#ifndef COMMON
#define COMMON

// general use libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

// Custom made macros

// Error unused variable solved
#define UNUSED(x) (void)(x)

// detect the function name
// end of macro definitions
#ifndef __FUNCTION_NAME__
    #ifdef WIN32   //WINDOWS
        #define __FUNCTION_NAME__   __FUNCTION__
    #else          //*NIX
        #define __FUNCTION_NAME__   __func__
    #endif
#endif

// clear screen macro
#define CLS() {system("@cls||clear");}

// macro definition for parameter validation
//
// PARAM can be the whole parameter or
// a component of it
/*
* NULL_PARAM_STRUCT_VALIDATION(PARAM)
* validates a parameter from a function that
* returns a data type or structure
*/
#define NULL_PARAM_STRUCT_VALIDATION(PARAM){\
			if(NULL == PARAM){\
				printf("\n\nNULL PARAMETER IN FUNCTION %s\n",__FUNCTION_NAME__);\
				CLS()\
				exit(-1);\
			}\
}

// custom defined boolean
typedef enum {false,true}bool;

typedef struct pieceCoordonate
{
	char piece;
	int x;
	int y;
}pieceCoordonate;

int matrixCmp(unsigned char**firstMatrix, unsigned char**secondMatrix);
// print the current matrix
void printMatrix(unsigned char** matrix);
// get the difference between the current and initial states
int diffStates(unsigned char**currentMatrix);
// get the total number of pieces in game
int countPieces(unsigned char**currentMatrix);

bool isCheckPlayerFromPawn(unsigned char **currentMatrix, pieceCoordonate *king);

bool isCheckAIFromPawn(unsigned char **currentMatrix, pieceCoordonate *king);

bool isCheckFromRook(unsigned char **currentMatrix, pieceCoordonate *king, char c);

bool isCheckFromBishop(unsigned char **currentMatrix, pieceCoordonate *king, char c);

bool isCheckFromQueen(unsigned char **currentMatrix, pieceCoordonate *king, char c);

bool isCheckFromKnight(unsigned char **currentMatrix, pieceCoordonate *king, char c);

bool isNotInCheckPlayer(unsigned char**currentMatrix);

bool isNotInCheckAI(unsigned char**currentMatrix);

#endif /* COMMON */
