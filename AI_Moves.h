#ifndef AI_Moves
#define AI_Moves

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

typedef struct Point
{
    int posX;
    int posY;
}coord;
/*
 * All functions will be called in:
 * getNextCoordForPiece()
 * functions for each piece:
 * Pawn -> pawnMovement
 * Knight -> knightMovement
 * Rook -> vertivalMove + horizontal
 * Bishop -> mainDiagonalMove
 * Queen -> secondaryDiagonalMove
 * King ->  getNextCoordForPiece
 * the functions will return the number of positions that change
 * 
 */ 
coord* horizontalMove(int posX, int posY, unsigned char** matrix);
coord* verticalMove(int posX, int posY, unsigned char** matrix);
// main diagonal is of the form i=j
coord* mainDiagonalMove(int posX, int posY, unsigned char** matrix);
// secondary diagonal is of the form i = nrCol - j - i
coord* secondaryDiagonalMove(int posX, int posY, unsigned char** matrix);
// pawn movement
coord* pawnMovement(int posX, int posY, unsigned char** matrix);
// knight movement
coord* knightMovement(int posX, int posY, unsigned char** matrix);
//get all the coordonates of the pieces of type "piece"
coord** getCoordPieces(unsigned char** matrix,unsigned char piece);
// function that interprets and returns the new state from the AI
unsigned char** getGeneralMatrixMove(unsigned char** matrix);

#endif /* AI_Moves*/