#ifndef GAME_LOGIC
#define GAME_LOGIC

// general use libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"

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