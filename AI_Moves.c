#include "AI_Moves.h"

coord* horizontalMove(int posX, int posY, unsigned char** matrix)
{
    char* userPieces = "rhbqkp";
    char* aiPieces = "RHBQKP";

    coord* returnValue = malloc(sizeof(coord));
    returnValue->posX = posX;
    returnValue->posY = posY;

    if(strchr(aiPieces,matrix[posY][posX+1])&&strchr(aiPieces,matrix[posY][posX-1]))
        return returnValue;
    else 
    {
        int * possibleMovement = malloc(sizeof(int)*8);
        int sizePossible = 0;
        //right movement
        for(int i = posX+1 ; i<=7;i++)
        {
            if((strchr(userPieces,matrix[posX][i])!=NULL || 
                matrix[posX][i]=='*')&&
                strchr(aiPieces,matrix[posY][i])==NULL)
            {
                possibleMovement[sizePossible++] = i;
                if(strchr(userPieces,matrix[posX][i])!=NULL)
                {
                    possibleMovement[sizePossible++] = i;
                    possibleMovement[sizePossible++] = i;
                }
            }
        }
        //left movement
        for(int i = posX-1 ; i>=0;i--)
        {
            if((strchr(userPieces,matrix[posX][i])!=NULL || 
                matrix[posX][i]=='*')&&
                strchr(aiPieces,matrix[posY][i])==NULL)
            {
                possibleMovement[sizePossible++] = i;
                if(strchr(userPieces,matrix[posX][i])!=NULL)
                {
                    possibleMovement[sizePossible++] = i;
                    possibleMovement[sizePossible++] = i;
                }
            }
        }
        srand(sizePossible);
        returnValue->posX = possibleMovement[rand()%sizePossible];
        return returnValue;
    }
        
    
}
coord* verticalMove(int posX, int posY, unsigned char** matrix)
{
    char* userPieces = "rhbqkp";
    char* aiPieces = "RHBQKP";

    coord* returnValue = malloc(sizeof(coord));
    returnValue->posX = posX;
    returnValue->posY = posY;

    if(strchr(aiPieces,matrix[posY+1][posX])&&strchr(aiPieces,matrix[posY-1][posX]))
        return returnValue;
    else 
    {
        int * possibleMovement = malloc(sizeof(int)*8);
        int sizePossible = 0;
        //right movement
        for(int i = posY+1 ; i<=7;i++)
        {
            if((strchr(userPieces,matrix[i][posX])!=NULL || 
                matrix[posX][i]=='*')&&
                strchr(aiPieces,matrix[i][posX])==NULL)
            {
                possibleMovement[sizePossible++] = i;
                if(strchr(userPieces,matrix[i][posX])!=NULL)
                {
                    possibleMovement[sizePossible++] = i;
                    possibleMovement[sizePossible++] = i;
                }
            }
        }
        //left movement
        for(int i = posY-1 ; i>=0;i--)
        {
            if((strchr(userPieces,matrix[i][posX])!=NULL || 
                matrix[posX][i]=='*')&&
                strchr(aiPieces,matrix[i][posX])==NULL)
            {
                possibleMovement[sizePossible++] = i;
                if(strchr(userPieces,matrix[i][posX])!=NULL)
                {
                    possibleMovement[sizePossible++] = i;
                    possibleMovement[sizePossible++] = i;
                }
            }
        }

        srand(sizePossible);
        returnValue->posY = possibleMovement[rand()%sizePossible];
        return returnValue;
    }
}
// main diagonal is of the form i=j
coord* mainDiagonalMove(int posX, int posY, unsigned char** matrix)
{
    char* userPieces = "rhbqkp";
    char* aiPieces = "RHBQKP";

    coord* returnValue = malloc(sizeof(coord));
    returnValue->posX = posX;
    returnValue->posY = posY;

    if(strchr(aiPieces,matrix[posY+1][posX+1])&&strchr(aiPieces,matrix[posY-1][posX-1]))
        return returnValue;
    else 
    {
        int * possibleMovement = malloc(sizeof(int)*8);
        int sizePossible = 0;
        //diagonal movement
        for(int i = -7 ; i<=7;i++)
        {
            //if the position is not on the board
            if(posY + i < 0 )
                continue;
            if(posX + i < 0 )
                continue;
            if(posX + i > 7)
                break;
            if(posY + i > 7)
                break;    
                
            // conditions for the move  
            if((strchr(userPieces,matrix[posY+i][posX+i])!=NULL || 
                matrix[posY+i][posX+i]=='*')&&
                strchr(aiPieces,matrix[posY+i][posX+i])==NULL)
            {
                possibleMovement[sizePossible++] = i;
                if(strchr(userPieces,matrix[posY+i][posX+i])!=NULL)
                {
                    possibleMovement[sizePossible++] = i;
                    possibleMovement[sizePossible++] = i;
                }
            }
        }

        srand(sizePossible);
        int diffMovement = possibleMovement[rand()%sizePossible];
        free(possibleMovement);
    
        returnValue->posX += diffMovement;
        returnValue->posY += diffMovement;
        return returnValue;
    }
}
// secondary diagonal is of the form i = nrCol - j - i
coord* secondaryDiagonalMove(int posX, int posY, unsigned char** matrix)
{
    char* userPieces = "rhbqkp";
    char* aiPieces = "RHBQKP";
    
    coord* returnValue = malloc(sizeof(coord));
    returnValue->posX = posX;
    returnValue->posY = posY;

    if(strchr(aiPieces,matrix[posY+1][posX-1])&&strchr(aiPieces,matrix[posY-1][posX+1]))
        return returnValue;
    else 
    {
        int * possibleMovement = malloc(sizeof(int)*8);
        int sizePossible = 0;
        //diagonal movement
        for(int i = -7 ; i<=7;i++)
        {
            //if the position is not on the board
            if(posY + i < 0 )
                continue;
            if(posX + i < 0 )
                continue;
            if(posX + i > 7)
                break;
            if(posY + i > 7)
                break;
                
            // conditions for the move
            if((strchr(userPieces,matrix[posY+i][posX-i])!=NULL || 
                matrix[posY+i][posX+i]=='*')&&
                strchr(aiPieces,matrix[posY+i][posX-i])==NULL)
            {
                possibleMovement[sizePossible++] = i;
                if(strchr(userPieces,matrix[posY+i][posX-i])!=NULL)
                {
                    possibleMovement[sizePossible++] = i;
                    possibleMovement[sizePossible++] = i;
                }
            }
        }

        srand(sizePossible);
        int diffMovement = possibleMovement[rand()%sizePossible];
        free(possibleMovement);

        returnValue->posX += diffMovement;
        returnValue->posY += diffMovement;
        return returnValue;
    }
}
// pawn movement
coord* pawnMovement(int posX, int posY, unsigned char** matrix)
{
    char* userPieces = "rhbqkp";
    char* aiPieces = "RHBQKP";
    
    coord* returnValue = malloc(sizeof(coord));
    returnValue->posX = posX;
    returnValue->posY = posY;

    // right attack
    if(strchr(userPieces,matrix[posY+1][posX+1]))
    {
            returnValue->posX ++;
            returnValue->posY ++;
            return returnValue;
    }
    // left attack
    if(strchr(userPieces,matrix[posY+1][posX-1]))
    {
            returnValue->posX --;
            returnValue->posY ++;
            return returnValue;
    }
    // impossible to move
    if(strchr(aiPieces,matrix[posY+1][posX])||strchr(userPieces,matrix[posY+1][posX]))
    {
            return returnValue;    
    }
    //move two spaces
    if(posY == 1 && !(strchr(aiPieces,matrix[posY+2][posX])||strchr(userPieces,matrix[posY+2][posX])))
    {
            returnValue->posY += 2;
            return returnValue;

    }

    returnValue->posY++;
    return returnValue;
}
// knight movement
coord* knightMovement(int posX, int posY, unsigned char** matrix)
{
    char* userPieces = "rhbqkp";
    char* aiPieces = "RHBQKP";

    // relative positions on the knight's move
    int xValues[8] = {-1,-2,-2,-1,1,2,2,1};
    int yValues[8] = {2,1,-1,-2,-2,-1,1,2};

    coord* returnValue = malloc(sizeof(coord));
    returnValue->posX = posX;
    returnValue->posY = posY;

    int * possibleMovement = malloc(sizeof(int)*8);
    int sizePossible = 0;

    for(int i=0;i<8;i++)
    {
        // conditions on the possible moves
        if(strchr(userPieces,matrix[posY+yValues[i]][posX+xValues[i]]) ||
            '*' == matrix[posY+yValues[i]][posX+xValues[i]] ||
            strchr(aiPieces,matrix[posY+yValues[i]][posX+xValues[i]])==NULL)
            {
                possibleMovement[sizePossible++] = i;
            }
    }

    srand(sizePossible);
    int diffMovement = possibleMovement[rand()%sizePossible];
    free(possibleMovement);
    
    returnValue->posX += xValues[diffMovement];
    returnValue->posY += yValues[diffMovement];
    return returnValue;
}
//get all the coordonates of the pieces of type "piece"
coord** getCoordPieces(unsigned char** matrix,unsigned char piece)
{
    coord** pieceCoord;
    int nrOfPieces = 0;
    //allocate memory for each of the pieces
    pieceCoord = malloc(sizeof(coord*)*8);

    nrOfPieces=0;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(matrix[i][j]==piece)
            {
                // insert the location of the piece into the return value
                pieceCoord[nrOfPieces++] = malloc(sizeof(coord));
                pieceCoord[nrOfPieces]->posX = j;
                pieceCoord[nrOfPieces]->posY = i;
            }
        }
    }

    //realocate to the exact number of pieces left
    pieceCoord = realloc(pieceCoord,sizeof(coord**)*(sizeof(pieceCoord)/sizeof(pieceCoord[0])));

    return pieceCoord;
    
}
// function that interprets and returns the new state from the AI
unsigned char** getGeneralMatrixMove(unsigned char** matrix)
{
    char* aiPieces = "PHBRQK";
    int pieceValue[6][3] = {{1,1,1},{3,4,5},{3,4,5},{5,6,7},{9,10,13},{0,1,1}};

    

    coord ** allPieces = malloc(sizeof(coord *));
    int nrOfPieces = 0;

    // select all locations of pieces
    for(int i=0;i<6;i++)
    {
        coord** pieceMoves = getCoordPieces(matrix,aiPieces[i]);
        int sizeAllocated = sizeof(pieceMoves)/sizeof(pieceMoves[0]);
        for(int j=0;j<sizeAllocated;j++)
        {
            allPieces = realloc(allPieces,
                                nrOfPieces+sizeAllocated);
            for(int k=0;k<sizeAllocated;k++)
            {
                allPieces[nrOfPieces++] = pieceMoves[k];
                free(pieceMoves[k]);
            }
            
        }
        // append the next state with the current piece
        for(int i=0;i<nrOfPieces;i++)
        {
            if()
        }

        free(pieceMoves);

    }

}