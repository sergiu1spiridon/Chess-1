#include "Game_Logic.h"

// get the difference between the current and initial states
int diffStates(unsigned char**currentMatrix)
{
    // the difference between the two Matrices
    int diffCount = 0;
    
    for(int i= 0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if((int)currentMatrix[i][j]!=(int)initialChessMatrix[i][j]) diffCount++;
        }
    }

    return diffCount;
}
// get the total number of pieces in game
int countPieces(unsigned char**currentMatrix)
{
    // the difference between the two Matrices
    int count = 0;
    
    for(int i= 0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(currentMatrix[i][j]!='*') count++;
        }
    }

    return count;
}
// get the key for the hashtable from the current state
unsigned char* getKeyFromChessTable(unsigned char**chessMatrix)
{
    unsigned char* local_key = malloc(sizeof(unsigned char)*192);

    for(unsigned int i = 0;i<8;i++)
    {
        for(unsigned int j=0;j<8;j++)
        {
            strcat(local_key,(char*)&chessMatrix[i][j]);
            strcat(local_key,(char*)&i);
            strcat(local_key,(char*)&j);

        }
    }
    printf("%s\n",local_key);
    return local_key;
}
// get the current state from the hashtable
unsigned char** getChessTableFromKey(unsigned char* key)
{
    unsigned char ** chessMatrix = malloc(sizeof(unsigned char*)*8);
    
    for(int i= 0;i<8;i++)
    {
        chessMatrix[i] = malloc(sizeof(unsigned char)*8);
        for(int j=0;j<24;j+=3)
        {
            strcpy((char*)&chessMatrix[j+1][j+2],(char*)&j);
        }
    }
    return chessMatrix;
}
// get the score of the state from the table
int getScoreFromChessTable(unsigned char* chessMatrixKey)
{
    return 0;
}
// get the best piece for the next move
unsigned char* getPieceFromChessTable(unsigned char** chessMatrix)
{
    int diffCount = diffStates(chessMatrix);
    int totalPieces = countPieces(chessMatrix);

    // early game is defined as diffCount < 16
    // middle game is defined as diffCount >= 16 and total pieces >=8
    // end game is otherwise

    if(diffCount < 16)
    {
        //early game
    }
    else if(diffCount >=16 && totalPieces >=8)
    {
        //middle game
    }
    else
    {
        //end game
    }
    
}
