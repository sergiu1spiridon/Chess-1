#ifndef GAME_LOGIC
#define GAME_LOGIC

#include "common.h"

// get the key for the hashtable from the current state
unsigned char* getKeyFromChessTable(unsigned char**chessMatrix);
// get the current state from the hashtable
unsigned char** getChessTableFromKey(unsigned char* key);
// get the score of the state from the table
int getScoreFromChessTable(unsigned char** chessMatrix);
// get the best piece for the next move
unsigned char* getPieceFromChessTable(unsigned char** chessMatrix);


#endif/*GAME_LOGIC*/