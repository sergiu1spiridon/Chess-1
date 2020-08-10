#include "Check_Mate.h"

unsigned char **movePawn(unsigned char **matrix, pieceCoordonate *myPiece) {
    unsigned char **newMat = malloc(sizeof(char *) * 8);
}

bool isInCheckMate(unsigned char **matrix) {
    pieceCoordonate *myPiece = malloc(sizeof(pieceCoordonate));

    for(int j = 0; j < 8; j++)
        for(int l = 0; l < 8; l++)
        {
            if (matrix[j][l] == 'p')
            {
                myPiece->piece = 'p';
                myPiece->y = j;
                myPiece->x = l;

                unsigned char** newMat = movePawn(matrix, myPiece);

                if (isNotInCheck(newMat))
                {
                    return 0;
                }
                
            }
            if (matrix[j][l] == 'r')
            {
                myPiece->piece = 'r';
                myPiece->y = j;
                myPiece->x = l;

                unsigned char** newMat = moveRook(matrix, myPiece);

                if (isNotInCheck(newMat))
                {
                    return 0;
                }
                
            }
            if (matrix[j][l] == 'h')
            {
                myPiece->piece = 'h';
                myPiece->y = j;
                myPiece->x = l;

                unsigned char** newMat = movehorse(matrix, myPiece);

                if (isNotInCheck(newMat))
                {
                    return 0;
                }
                
            }
            if (matrix[j][l] == 'h')
            {
                myPiece->piece = 'h';
                myPiece->y = j;
                myPiece->x = l;

                unsigned char** newMat = moveKnight(matrix, myPiece);

                if (isNotInCheck(newMat))
                {
                    return 0;
                }
                
            }
            if (matrix[j][l] == 'q')
            {
                myPiece->piece = 'q';
                myPiece->y = j;
                myPiece->x = l;

                unsigned char** newMat = moveQueen(matrix, myPiece);

                if (isNotInCheck(newMat))
                {
                    return 0;
                }
                
            }
            if (matrix[j][l] == 'k')
            {
                myPiece->piece = 'k';
                myPiece->y = j;
                myPiece->x = l;

                unsigned char** newMat = moveKing(matrix, myPiece);

                if (isNotInCheck(newMat))
                {
                    return 0;
                }
                
            }
    }
    return 1;
}