#ifndef CHECK_MATE
#define CHECK_MATE

// general use libraries
#include "common.h"

bool movePawn(unsigned char **matrix, pieceCoordonate *myPiece);

bool moveRook(unsigned char **matrix, pieceCoordonate *myPiece);

bool moveBishop(unsigned char **matrix, pieceCoordonate *myPiece);

bool moveKnight(unsigned char **matrix, pieceCoordonate *myPiece);

bool moveQueen(unsigned char **matrix, pieceCoordonate *myPiece);

bool moveKing(unsigned char **matrix, pieceCoordonate *myPiece);

bool isInCheckMate(unsigned char** matrix);

#endif /* CHECK_MATE */