#ifndef GAME_LOGIC
#define GAME_LOGIC

// general use libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Hashtable.h"
#include "AI_Moves.h"
#include "common.h"
/* 
 * Legend for encryption of pieces:
 * P - AI pawn
 * H - AI knight
 * B - AI bishop
 * R - AI rook
 * Q - AI queen
 * K - AI king
 * 
 * p - user pawn
 * h - user knight
 * b - user bishop
 * r - user rook
 * q - user queen
 * k - user king
 *
 * Piece values per type of game:
 * |Piece    |EarlyGame|MiddleGame|EndGame|
 * |P(pawn)  |    01   |    01    |   01  |
 * |H(knight)|    03   |    04    |   05  |
 * |B(bishop)|    03   |    04    |   05  |
 * |R(rook)  |    05   |    06    |   07  |
 * |Q(queen) |    09   |    10    |   13  |
 * |K(king)  |    00   |    01    |   01  |
 *  
*/

// get the key for the hashtable from the current state
unsigned char* getKeyFromChessTable(unsigned char**chessMatrix);
// get the current state from the hashtable
unsigned char** getChessTableFromKey(unsigned char* key);
// get the score of the state from the key of the table
int getStateScore(unsigned char *chessMatrixKey);
// get the score of the state from the table
int addChildToParent(hashtable *hash, unsigned char* chessMatrixKey, unsigned char* parentKey);
// get the move thats on top of the heap of curent one
unsigned char* getNextMove(hashtable *hash, unsigned char* currentMoveKey);


#endif/*GAME_LOGIC*/