#ifndef GAME_LOGIC
#define GAME_LOGIC

// general use libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"
/*
* Score value is calculated by the formula:
* Sum of current pieces +
* 
* 
* Chess encoding:
* P - Pawn
* k - knight
* B - bishop
* R - rook
* Q - queen
* K - king
* 
* 
*/
//extern char pieceValue[7][8];
/*
={ "PEGMGEG",
"P010101",
"k030405",
"B030405",
"R050607",
"Q091013",
"K000101"};
*/
/*
 * Initial chess matrix
*/
//extern char initialChessMatrix[8][8];
/*
  ={"RkBQKBkR",
    "PPPPPPPP",
    "********",
    "********",
    "********",
    "********",
    "PPPPPPPP",
    "RkBQKBkR"};
*/
// get the difference between the current and initial states
int diffStates(unsigned char**currentMatrix);
// get the total number of pieces in game
int countPieces(unsigned char**currentMatrix);
// get the key for the hashtable from the current state
unsigned char* getKeyFromChessTable(unsigned char**chessMatrix);
// get the current state from the hashtable
unsigned char** getChessTableFromKey(unsigned char* key);
// get the score of the state from the table
int getScoreFromChessTable(unsigned char* chessMatrixKey);
// get the best piece for the next move
unsigned char* getPieceFromChessTable(unsigned char** chessMatrix);


#endif/*GAME_LOGIC*/