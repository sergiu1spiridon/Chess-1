#ifndef PIECES_MOVES
#define PIECES_MOVES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


#endif /* PIECES_MOVES*/