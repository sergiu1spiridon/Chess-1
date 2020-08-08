#include "Pieces_Moves.h"

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
            if(posY + i < 0 )
                continue;
            if(posX + i < 0 )
                continue;
            if(posX + i > 7)
                break;
            if(posY + i > 7)
                break;      
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
            if(posY + i < 0 )
                continue;
            if(posX + i < 0 )
                continue;
            if(posX + i > 7)
                break;
            if(posY + i > 7)
                break;
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

    int xValues[8] = {-1,-2,-2,-1,1,2,2,1};
    int yValues[8] = {2,1,-1,-2,-2,-1,1,2};

    coord* returnValue = malloc(sizeof(coord));
    returnValue->posX = posX;
    returnValue->posY = posY;

    int * possibleMovement = malloc(sizeof(int)*8);
    int sizePossible = 0;

    for(int i=0;i<8;i++)
    {
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