#include "AI_Move.h"


unsigned char** getFutureMatrix(coord* position, unsigned char** currentMatrix)
{
    unsigned char** futureMatrix = currentMatrix;
    futureMatrix[position->posY][position->posX] = position->typePiece;
    futureMatrix[position->posY_initial][position->posX] = position->typePiece;

    return futureMatrix;
}

coord* horizontalMove(int posX, int posY, unsigned char** matrix,unsigned char typePiece)
{
    char* userPieces = "rhbqkp";

    coord* returnValue = malloc(sizeof(coord));
    returnValue->posX = posX;
    returnValue->posX_initial = posX;
    returnValue->posY = posY;
    returnValue->posY_initial = posY;
    returnValue->typePiece = typePiece;


    int * possibleMovement = malloc(sizeof(int)*16);
    int sizePossible = 0;
    //right movement
    for(int i = posX+1 ; i<=7;i++)
    {
        if(strchr(userPieces,matrix[posX][i]) || 
            matrix[posX][i]=='*')
        {
            if(isNotInCheckAI(getFutureMatrix(returnValue,matrix)))
            {
                possibleMovement[sizePossible++] = i;
                possibleMovement[sizePossible++] = i;
            }
        }
    }
    //left movement
    for(int i = posX-1 ; i>=0;i--)
    {
        if((strchr(userPieces,matrix[posX][i]) || 
            matrix[posX][i]=='*'))
        {
            if(isNotInCheckAI(getFutureMatrix(returnValue,matrix)))
            {
                possibleMovement[sizePossible++] = i;
                possibleMovement[sizePossible++] = i;
            }
        }
    }
    srand(sizePossible);
    if(sizePossible==0)
        return NULL;
    returnValue->posX = possibleMovement[rand()%sizePossible];
    return returnValue;
    
        
    
}
coord* verticalMove(int posX, int posY, unsigned char** matrix,unsigned char typePiece)
{
    char* userPieces = "rhbqkp";

    coord* returnValue = malloc(sizeof(coord));
    returnValue->posX = posX;
    returnValue->posX_initial = posX;
    returnValue->posY = posY;
    returnValue->posY_initial = posY;     
    returnValue->typePiece = typePiece;

    int * possibleMovement = malloc(sizeof(int)*16);
    int sizePossible = 0;
    //down movement
    for(int i = posY+1 ; i<=7;i++)
    {
        if((strchr(userPieces,matrix[i][posX]) || 
            matrix[i][posX]=='*'))
        {
            if(isNotInCheckAI(getFutureMatrix(returnValue,matrix)))
            {
                possibleMovement[sizePossible++] = i;
                possibleMovement[sizePossible++] = i;
            }
        }
    }
    //up movement
    for(int i = posY-1 ; i>=0;i--)
    {
        if(strchr(userPieces,matrix[i][posX]) || 
            matrix[i][posX]=='*')
        {
            if(isNotInCheckAI(getFutureMatrix(returnValue,matrix)))
            {
                possibleMovement[sizePossible++] = i;
                possibleMovement[sizePossible++] = i;
            }
        }
    }

    srand(sizePossible);
    if(sizePossible==0)
        return NULL;
    returnValue->posY = possibleMovement[rand()%sizePossible];
    return returnValue;
    
}
// main diagonal is of the form i=j
coord* mainDiagonalMove(int posX, int posY, unsigned char** matrix,unsigned char typePiece)
{
    char* userPieces = "rhbqkp";

    coord* returnValue = malloc(sizeof(coord));
    returnValue->posX = posX;
    returnValue->posX_initial = posX;
    returnValue->posY = posY;
    returnValue->posY_initial = posY;     
    returnValue->typePiece = typePiece;


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
        if(strchr(userPieces,matrix[posY+i][posX+i]) || 
            matrix[posY+i][posX+i]=='*')
        {
            if(isNotInCheckAI(getFutureMatrix(returnValue,matrix)))
            {
                possibleMovement[sizePossible++] = i;
                possibleMovement[sizePossible++] = i;
            }
        }
    }

    srand(sizePossible);
    if(sizePossible==0)
        return NULL;
    int diffMovement = possibleMovement[rand()%sizePossible];
    free(possibleMovement);

    returnValue->posX += diffMovement;
    returnValue->posY += diffMovement;
    return returnValue;
}
// secondary diagonal is of the form i = nrCol - j - i
coord* secondaryDiagonalMove(int posX, int posY, unsigned char** matrix, unsigned char typePiece)
{
    char* userPieces = "rhbqkp";
    
    coord* returnValue = malloc(sizeof(coord));
    returnValue->posX = posX;
    returnValue->posX_initial = posX;
    returnValue->posY = posY;
    returnValue->posY_initial = posY;     
    returnValue->typePiece = typePiece;

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
        if(strchr(userPieces,matrix[posY+i][posX-i]) || 
            matrix[posY+i][posX+i]=='*')
        {
            if(isNotInCheckAI(getFutureMatrix(returnValue,matrix)))
            {
                possibleMovement[sizePossible++] = i;
                possibleMovement[sizePossible++] = i;
            }
            

        }
    }

    srand(sizePossible);
    if(sizePossible==0)
        return NULL;
    int diffMovement = possibleMovement[rand()%sizePossible];
    free(possibleMovement);

    returnValue->posX += diffMovement;
    returnValue->posY += diffMovement;
    return returnValue;
    
}
// pawn movement
coord* pawnMovement(int posX, int posY, unsigned char** matrix)
{
    char* userPieces = "rhbqkp";
    char* aiPieces = "RHBQKP";
    
    coord* returnValue = malloc(sizeof(coord));
    returnValue->posX = posX;
    returnValue->posX_initial = posX;
    returnValue->posY = posY;
    returnValue->posY_initial = posY;     
    returnValue->typePiece = 'P';

    // right attack
    if(!(posY + 1 > 7 || posX + 1 > 7) && strchr(userPieces,matrix[posY+1][posX+1]))
    {
            returnValue->posX ++;
            returnValue->posY ++;
            
            if(isNotInCheckAI(getFutureMatrix(returnValue,matrix)))
            {
                   return returnValue;
            }  
            returnValue->posX = returnValue->posX_initial;
            returnValue->posY = returnValue->posY_initial;
            
    }
    // left attack
    if(!(posY + 1 > 7 || posX - 1 > 7) && strchr(userPieces,matrix[posY+1][posX-1]))
    {
            returnValue->posX --;
            returnValue->posY ++;
            if(isNotInCheckAI(getFutureMatrix(returnValue,matrix)))
            {
                   return returnValue;
            }  
            returnValue->posX = returnValue->posX_initial;
            returnValue->posY = returnValue->posY_initial;
    }
    // impossible to move
    if(!(posY + 1 > 7 || posX > 7) && (strchr(aiPieces,matrix[posY+1][posX])||strchr(userPieces,matrix[posY+1][posX])))
    {
            if(isNotInCheckAI(getFutureMatrix(returnValue,matrix)))
            {
                   return returnValue;
            }  
            returnValue->posX = returnValue->posX_initial;
            returnValue->posY = returnValue->posY_initial;    
    }
    //move two spaces
    if(posY == 1 && !(strchr(aiPieces,matrix[posY+2][posX])||strchr(userPieces,matrix[posY+2][posX])))
    {
            returnValue->posY += 2;
            if(isNotInCheckAI(getFutureMatrix(returnValue,matrix)))
            {
                   return returnValue;
            }  
            returnValue->posX = returnValue->posX_initial;
            returnValue->posY = returnValue->posY_initial;

    }

    returnValue->posY++;
    if(isNotInCheckAI(getFutureMatrix(returnValue,matrix)))
    {
            return returnValue;
    }  
    returnValue->posX = returnValue->posX_initial;
    returnValue->posY = returnValue->posY_initial;
    return returnValue;
}
// knight movement
coord* knightMovement(int posX, int posY, unsigned char** matrix)
{
    char* userPieces = "rhbqkp";

    // relative positions on the knight's move
    int xValues[8] = {-1,-2,-2,-1,1,2,2,1};
    int yValues[8] = {2,1,-1,-2,-2,-1,1,2};

    coord* returnValue = malloc(sizeof(coord));
    returnValue->posX = posX;
    returnValue->posY = posY;
    returnValue->posX_initial = posX;
    returnValue->posY_initial = posY;
    returnValue->typePiece = 'H';

    int * possibleMovement = malloc(sizeof(int)*8);
    int sizePossible = 0;

    for(int i=0;i<8;i++)
    {
        // conditions on the possible moves
        if(posY+yValues[i] < 0 || posY+yValues[i] > 7 ||
           posX+xValues[i] < 0 || posX+xValues[i]> 7 )
            continue;
        if(strchr(userPieces,(char)(matrix[posY+yValues[i]][posX+xValues[i]])) ||
            '*' == matrix[posY+yValues[i]][posX+xValues[i]])
            {
                if(isNotInCheckAI(getFutureMatrix(returnValue,matrix)))
                {
                   possibleMovement[sizePossible++] = i;
                }  
            }
    }

    srand(sizePossible);
    if(sizePossible==0)
        return NULL;
    int diffMovement = possibleMovement[rand()%sizePossible];
    free(possibleMovement);
    
    returnValue->posX += xValues[diffMovement];
    returnValue->posY += yValues[diffMovement];
    return returnValue;
}
// king movement
coord* kingMovement(int posX,int posY,unsigned char**matrix)
{
    char* userPieces = "rhbqkp";

    // relative positions on the king's move
    int xValues[8] = {1 ,1,1,0,-1,-1,-1, 0};
    int yValues[8] = {-1,0,1,1, 1, 0,-1,-1};
    
    coord* returnValue = malloc(sizeof(coord));
    returnValue->posX = posX;
    returnValue->posX_initial = posX;
    returnValue->posY = posY;
    returnValue->posY_initial = posY;     
    returnValue->typePiece = 'K';

    int * possibleMovement = malloc(sizeof(int)*8);
    int sizePossible = 0;

    for(int i=0;i<8;i++)
    {
        if(posY+yValues[i] < 0 || posY+yValues[i] > 7 ||
            posX+xValues[i]< 0 || posX+xValues[i] > 7)
            continue;

        if(strchr(userPieces,matrix[posY+yValues[i]][posX+xValues[i]]) ||
           '*' == matrix[posY+yValues[i]][posX+xValues[i]])
           {
               if(isNotInCheckAI(matrix))
               {
                   possibleMovement[sizePossible++] = i;
               }     
           }
    }

    srand(sizePossible);
    if(sizePossible==0)
        return NULL;
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
                pieceCoord[nrOfPieces] = malloc(sizeof(coord));
                pieceCoord[nrOfPieces]->posX = j;
                pieceCoord[nrOfPieces]->posX_initial = j;
                pieceCoord[nrOfPieces]->posY = i;
                pieceCoord[nrOfPieces]->posY_initial = i;
                pieceCoord[nrOfPieces]->typePiece = piece;
                nrOfPieces++;

            }
        }
    }
    //realocate to the exact number of pieces left
    pieceCoord = realloc(pieceCoord,sizeof(coord*)*(nrOfPieces+1));
    pieceCoord[nrOfPieces] = NULL;

    return pieceCoord;
    
}
// returns the set of identifiers of pieces
void switchPieces(coord** allPieces, unsigned char piece, int *nrOfPieces,
                 coord*currentPieceLocation,unsigned char** matrix,int typeGame)
{
    int pieceValue[6][3] = {{1,1,1},{3,4,5},{3,4,5},{5,6,7},{9,10,13},{0,1,1}};
    int currentNrOfPieces= *nrOfPieces;
    int prob = 0;
    switch (piece)
    {
        case 'P':
            for(prob = 0;prob<pieceValue[0][typeGame];prob++)
            {
                coord *newCoord = malloc(sizeof(coord));
                newCoord->typePiece = 'P';
                allPieces[currentNrOfPieces] = newCoord;
                allPieces[currentNrOfPieces] = pawnMovement( currentPieceLocation->posX,
                                                        currentPieceLocation->posY,
                                                        matrix);
                if(allPieces[currentNrOfPieces]!=NULL)
                    currentNrOfPieces++;
            }
            break;
        case 'H':
            for(prob = 0;prob<pieceValue[1][typeGame];prob++)
            {
                
                allPieces[currentNrOfPieces] = malloc(sizeof(coord));
                
                allPieces[currentNrOfPieces]->typePiece = 'H';
                allPieces[currentNrOfPieces] = knightMovement(currentPieceLocation->posX,
                                                            currentPieceLocation->posY,
                                                            matrix);
                if(allPieces[currentNrOfPieces]!=NULL)
                    currentNrOfPieces++;
            }
                
            break;
        case 'B':
            for(prob = 0;prob<pieceValue[2][typeGame];prob++)
            {
                
                allPieces[currentNrOfPieces] = malloc(sizeof(coord));
                
                allPieces[currentNrOfPieces]->typePiece = 'B';
                allPieces[currentNrOfPieces] = mainDiagonalMove( currentPieceLocation->posX,
                                                            currentPieceLocation->posY,
                                                            matrix,piece);
                if(allPieces[currentNrOfPieces]!=NULL)
                    currentNrOfPieces++;
                allPieces[currentNrOfPieces] = malloc(sizeof(coord));
                
                allPieces[currentNrOfPieces]->typePiece = 'B';
                allPieces[currentNrOfPieces] = secondaryDiagonalMove(currentPieceLocation->posX,
                                                                currentPieceLocation->posY,
                                                                matrix,piece);
                if(allPieces[currentNrOfPieces]!=NULL)
                    currentNrOfPieces++;
            }
            break;
        case 'R':
            for(prob = 0;prob<pieceValue[3][typeGame];prob++)
            {
                allPieces[currentNrOfPieces] = malloc(sizeof(coord));
                
                allPieces[currentNrOfPieces]->typePiece = 'R';
                allPieces[currentNrOfPieces] = horizontalMove(currentPieceLocation->posX,
                                                            currentPieceLocation->posY,
                                                            matrix,piece);
                if(allPieces[currentNrOfPieces]!=NULL)
                    currentNrOfPieces++;
                allPieces[currentNrOfPieces] = malloc(sizeof(coord));
                
                allPieces[currentNrOfPieces]->typePiece = 'R';
                allPieces[currentNrOfPieces] = verticalMove( currentPieceLocation->posX,
                                                        currentPieceLocation->posY,
                                                        matrix,piece);
                if(allPieces[currentNrOfPieces]!=NULL)
                    currentNrOfPieces++;
            }
            break;
        case 'Q':
            for(prob = 0;prob<pieceValue[4][typeGame];prob++)
            {
                
                allPieces[currentNrOfPieces] = malloc(sizeof(coord));
                
                allPieces[currentNrOfPieces]->typePiece = 'Q';
                allPieces[currentNrOfPieces] = mainDiagonalMove( currentPieceLocation->posX,
                                                            currentPieceLocation->posY,
                                                            matrix,piece);
                if(allPieces[currentNrOfPieces]!=NULL)
                    currentNrOfPieces++;
                allPieces[currentNrOfPieces] = malloc(sizeof(coord));
                
                allPieces[currentNrOfPieces]->typePiece = 'Q';
                allPieces[currentNrOfPieces] = secondaryDiagonalMove(currentPieceLocation->posX,
                                                                currentPieceLocation->posY,
                                                                matrix,piece);
                if(allPieces[currentNrOfPieces]!=NULL)
                    currentNrOfPieces++;
                allPieces[currentNrOfPieces] = malloc(sizeof(coord));
                
                allPieces[currentNrOfPieces]->typePiece = 'Q';
                allPieces[currentNrOfPieces] = horizontalMove(currentPieceLocation->posX,
                                                            currentPieceLocation->posY,
                                                            matrix,piece);
                if(allPieces[currentNrOfPieces]!=NULL)
                    currentNrOfPieces++;
                allPieces[currentNrOfPieces] = malloc(sizeof(coord));
                
                allPieces[currentNrOfPieces]->typePiece = 'Q';
                allPieces[currentNrOfPieces] = verticalMove( currentPieceLocation->posX,
                                                        currentPieceLocation->posY,
                                                        matrix,piece);
                if(allPieces[currentNrOfPieces]!=NULL)
                    currentNrOfPieces++;
            }
            break;
        case 'K':
            for(prob = 0;prob<pieceValue[5][typeGame];prob++)
            {   
                allPieces[currentNrOfPieces] = malloc(sizeof(coord));
                
                allPieces[currentNrOfPieces]->typePiece = 'K';
                allPieces[currentNrOfPieces] = kingMovement(currentPieceLocation->posX,
                    currentPieceLocation->posY,matrix);
                if(allPieces[currentNrOfPieces]!=NULL)
                    currentNrOfPieces++;
            }
            break;
        default:
            break;
    }
    *nrOfPieces = currentNrOfPieces;
}
// function that interprets and returns the new state from the AI
unsigned char** getAIMove(unsigned char** matrix)
{
    // check for check and try to find a solution


    // normal play
    char* aiPieces = "PHBRQK";

    coord ** allPieces = calloc(sizeof(coord *),1024);
    int nrOfMoves = 0;

    // select all locations of pieces
    for(int i=0;i<6;i++)
    {
        coord** currentPieceLocation = getCoordPieces(matrix,aiPieces[i]);
        
        int sizeAllocated = 0;

        while(currentPieceLocation[sizeAllocated]!=NULL)
        {
            sizeAllocated++;
        }


        for(int k=0;k<sizeAllocated;k++)
        {
            int diffCount = diffStates(matrix);
            int totalPieces = countPieces(matrix);

            // early game is defined as diffCount < 16
            // middle game is defined as diffCount >= 16 and total pieces >=8
            // end game is otherwise

            if(diffCount < 16)
            {
                //early game, get the first row of the pieceValue
                switchPieces(allPieces,aiPieces[i],&nrOfMoves,currentPieceLocation[k],matrix,0); 
            }
            else if(diffCount >=16 && totalPieces >=8)
            {
                //middle game, get the second row of the pieceValue
                switchPieces(allPieces,aiPieces[i],&nrOfMoves,currentPieceLocation[k],matrix,1);
            }
            else
            {
                //end game,, get the third row of the pieceValue
                switchPieces(allPieces,aiPieces[i],&nrOfMoves,currentPieceLocation[k],matrix,2);
            }
            free(currentPieceLocation[k]);
        }
        // append the next state with the current piece
        free(currentPieceLocation);
    }

    srand(nrOfMoves);
    if(NULL == allPieces[0])
    {
        return matrix;
    }
    coord* aiMove = allPieces[rand()%nrOfMoves];

    matrix[aiMove->posY_initial][aiMove->posX_initial]='*';

    return matrix;
}