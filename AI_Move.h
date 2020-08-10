#ifndef AI_Moves
#define AI_Moves

#include "common.h"

typedef struct Point
{
    int posX;
    int posY;
    int posX_initial;
    int posY_initial;
    char typePiece;
}coord;
/*
 * All functions will be called in:
 * getGeneralMatrixMove()
 * functions for each piece:
 * Pawn -> pawnMovement
 * Knight -> knightMovement
 * Rook -> vertivalMove + horizontal
 * Bishop -> mainDiagonalMove
 * Queen -> secondaryDiagonalMove
 * King ->  kingMovement
 * the functions will return the number of positions that change
 * 
 */ 
unsigned char** getFutureMatrix(coord* position, unsigned char** currentMatrix);
coord* horizontalMove(int posX, int posY, unsigned char** matrix,unsigned char typePiece);
coord* verticalMove(int posX, int posY, unsigned char** matrix,unsigned char typePiece);
// main diagonal is of the form i=j
coord* mainDiagonalMove(int posX, int posY, unsigned char** matrix,unsigned char typePiece);
// secondary diagonal is of the form i = nrCol - j - i
coord* secondaryDiagonalMove(int posX, int posY, unsigned char** matrix,unsigned char typePiece);
// pawn movement
coord* pawnMovement(int posX, int posY, unsigned char** matrix);
// knight movement
coord* knightMovement(int posX, int posY, unsigned char** matrix);
// king movement
coord* kingMovement(int posX,int posY,unsigned char** matrix);
//get all the coordonates of the pieces of type "piece"
coord** getCoordPieces(unsigned char** matrix,unsigned char piece);
// returns the set of identifiers of pieces
void switchPieces(coord** allPieces, unsigned char piece, int *nrOfPieces,
                 coord*currentPieceLocation,unsigned char** matrix,int typeGame);
// function that interprets and returns the new state from the AI
unsigned char** getAIMove(unsigned char** matrix);
#endif /* AI_Moves*/