#include "Check_Mate.h"

bool movePawn(unsigned char **matrix, pieceCoordonate *myPiece) {
    unsigned char **newMat = malloc(sizeof(char *) * 8);
    char *pieseleMele = "pkqrhb*";
    for(int i = 0; i < 8; i++)
        newMat[i] = malloc(sizeof(char) * 8);

    newMat = memcpy(newMat, matrix, 64);

    int sgny[4] = {-1,-2,-1,-1};
    int sgnx[4] = {0,0,-1,1};

    for (int i = 0; i < 2; i++)
    {
        if(matrix[myPiece->y + sgny[i]][myPiece->x + sgnx[i]] == '*') {
            newMat[myPiece->y + sgny[i]][myPiece->x + sgnx[i]] = 'p';
            newMat[myPiece->y][myPiece->x] = '*';
            if (isNotInCheckPlayer(newMat))
            {
                return 1;
            }
            newMat[myPiece->y + sgny[i]][myPiece->x + sgnx[i]] = matrix[myPiece->y][myPiece->x];
            newMat[myPiece->y][myPiece->x] = 'p';
            
        }
    }
    for (int i = 2; i < 4; i++)
    {
        if(strchr(pieseleMele, matrix[myPiece->y + sgny[i]][myPiece->x + sgnx[i]]) == NULL) {
            newMat[myPiece->y + sgny[i]][myPiece->x + sgnx[i]] = 'p';
            newMat[myPiece->y][myPiece->x] = '*';
            if (isNotInCheckPlayer(newMat))
            {
                return 1;
            }
            newMat[myPiece->y + sgny[i]][myPiece->x + sgnx[i]] = matrix[myPiece->y][myPiece->x];
            newMat[myPiece->y][myPiece->x] = 'p';
        }
    }

    return 0;
}

bool moveRook(unsigned char **matrix, pieceCoordonate *myPiece) {
    unsigned char **newMat = malloc(sizeof(char *) * 8);
    char *pieseleMele = "pkqrhb";
    for(int i = 0; i < 8; i++)
        newMat[i] = malloc(sizeof(char) * 8);

    newMat = memcpy(newMat, matrix, 64);

    int sgny[4] = {-1,1,0,0};
    int sgnx[4] = {0,0,-1,1};
    int x,y;
    for (int i = 0; i < 4; i++)
    {
        x = myPiece->x + sgnx[i];
        y = myPiece->y + sgny[i];
        while (x >= 0 && x <= 7 && y >= 0 && y <= 7)
        {
            if(strchr(pieseleMele, matrix[y][x]) == NULL) {
                newMat[y][x] = 'r';
                newMat[myPiece->y][myPiece->x] = '*';

                if (isNotInCheckPlayer(newMat)) {
                    return 1;
                }
                newMat[y][x] = matrix[y][x];
                newMat[myPiece->y][myPiece->x] = 'r';
                if(matrix[x][y] != '*')
                {
                    break;
                }            
            }
            else
                break;
            
            x += sgnx[i];
            y += sgny[i];
        }
    }

    return 0;
}

bool moveBishop(unsigned char **matrix, pieceCoordonate *myPiece) {
    unsigned char **newMat = malloc(sizeof(char *) * 8);
    char *pieseleMele = "pkqrhb";
    for(int i = 0; i < 8; i++)
        newMat[i] = malloc(sizeof(char) * 8);

    newMat = memcpy(newMat, matrix, 64);

    int sgny[4] = {-1,-1,1,1};
    int sgnx[4] = {-1,1,-1,1};
    int x,y;
    for (int i = 0; i < 4; i++)
    {
        x = myPiece->x + sgnx[i];
        y = myPiece->y + sgny[i];
        while (x >= 0 && x <= 7 && y >= 0 && y <= 7)
        {
            if(strchr(pieseleMele, matrix[y][x]) == NULL) {
                newMat[y][x] = 'b';
                newMat[myPiece->y][myPiece->x] = '*';

                if (isNotInCheckPlayer(newMat)) {
                    return 1;
                }
                newMat[y][x] = matrix[y][x];
                newMat[myPiece->y][myPiece->x] = 'b';

                if (matrix[y][x] != '*')
                {
                    break;
                }                
            }
            else
                break;
            
            x += sgnx[i];
            y += sgny[i];
        }
    }

    return 0;
}

bool moveKnight(unsigned char **matrix, pieceCoordonate *myPiece) {
    unsigned char **newMat = malloc(sizeof(char *) * 8);
    char *pieseleMele = "pkqrhb";
    for(int i = 0; i < 8; i++)
        newMat[i] = malloc(sizeof(char) * 8);

    newMat = memcpy(newMat, matrix, 64);

    int sgny[8] = {-1,-1,1,1,-2,-2,2,2};
    int sgnx[8] = {-2,2,-2,2,-1,1,-1,1};
    int x,y;
    for (int i = 0; i < 8; i++)
    {
        x = myPiece->x + sgnx[i];
        y = myPiece->y + sgny[i];
        if (x >= 0 && x <= 7 && y >= 0 && y <= 7)
        {
            if(strchr(pieseleMele, matrix[y][x]) == NULL) {
                newMat[y][x] = 'h';
                newMat[myPiece->y][myPiece->x] = '*';

                if (isNotInCheckPlayer(newMat)) {
                    return 1;
                }
                newMat[y][x] = matrix[y][x];
                newMat[myPiece->y][myPiece->x] = 'h';
            }
        }
    }

    return 0;
}

bool moveQueen(unsigned char **matrix, pieceCoordonate *myPiece) {
    unsigned char **newMat = malloc(sizeof(char *) * 8);
    char *pieseleMele = "pkqrhb";
    for(int i = 0; i < 8; i++)
        newMat[i] = malloc(sizeof(char) * 8);

    newMat = memcpy(newMat, matrix, 64);

    int sgny[8] = {-1,-1,1,1,-1,1,0,0};
    int sgnx[8] = {-1,1,-1,1,0,0,-1,1};
    int x,y;
    for (int i = 0; i < 8; i++)
    {
        x = myPiece->x + sgnx[i];
        y = myPiece->y + sgny[i];
        while (x >= 0 && x <= 7 && y >= 0 && y <= 7)
        {
            if(strchr(pieseleMele, matrix[y][x]) == NULL) {
                newMat[y][x] = 'q';
                newMat[myPiece->y][myPiece->x] = '*';

                if (isNotInCheckPlayer(newMat)) {
                    return 1;
                }
                newMat[y][x] = matrix[y][x];
                newMat[myPiece->y][myPiece->x] = 'q';

                if (newMat[y][x] != '*';)
               {
                   break;
               }           
            }
            else
                break;
            
            x += sgnx[i];
            y += sgny[i];
        }
    }

    return 0;
}

bool moveKing(unsigned char **matrix, pieceCoordonate *myPiece) {
    unsigned char **newMat = malloc(sizeof(char *) * 8);
    char *pieseleMele = "pkqrhb";
    for(int i = 0; i < 8; i++)
        newMat[i] = malloc(sizeof(char) * 8);

    newMat = memcpy(newMat, matrix, 64);

    int sgny[8] = {-1,-1,1,1,-1,1,0,0};
    int sgnx[8] = {-1,1,-1,1,0,0,-1,1};
    int x,y;
    for (int i = 0; i < 8; i++)
    {
        x = myPiece->x + sgnx[i];
        y = myPiece->y + sgny[i];
        if (x >= 0 && x <= 7 && y >= 0 && y <= 7)
        {
            if(strchr(pieseleMele, matrix[y][x]) == NULL) {
                newMat[y][x] = 'k';
                newMat[myPiece->y][myPiece->x] = '*';

                if (isNotInCheckPlayer(newMat)) {
                    return 1;
                }
                newMat[y][x] = matrix[y][x];
                newMat[myPiece->y][myPiece->x] = 'k';                
            }
        }
    }

    return 0;
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

                if (movePawn(matrix, myPiece))
                {
                    return 0;
                }
                
            }
            if (matrix[j][l] == 'r')
            {
                myPiece->piece = 'r';
                myPiece->y = j;
                myPiece->x = l;

                if (moveRook(matrix, myPiece))
                {
                    return 0;
                }
                
            }
            if (matrix[j][l] == 'h')
            {
                myPiece->piece = 'h';
                myPiece->y = j;
                myPiece->x = l;

                if (moveKnight(matrix, myPiece))
                {
                    return 0;
                }
                
            }
            if (matrix[j][l] == 'b')
            {
                myPiece->piece = 'b';
                myPiece->y = j;
                myPiece->x = l;

                if (moveBishop(matrix, myPiece))
                {
                    return 0;
                }
                
            }
            if (matrix[j][l] == 'q')
            {
                myPiece->piece = 'q';
                myPiece->y = j;
                myPiece->x = l;

                if (moveQueen(matrix, myPiece))
                {
                    return 0;
                }
                
            }
            if (matrix[j][l] == 'k')
            {
                myPiece->piece = 'k';
                myPiece->y = j;
                myPiece->x = l;

                if (moveKing(matrix, myPiece))
                {
                    return 0;
                }
                
            }
    }
    return 1;
}