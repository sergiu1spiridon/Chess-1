#include "Game_Logic.h"

/*
 * Initial chess matrix
*/


// get the difference between the current and initial states
int diffStates(unsigned char**currentMatrix)
{

    char initialChessMatrix[8][8]
  ={"RHBQKBHR",
    "PPPPPPPP",
    "********",
    "********",
    "********",
    "********",
    "pppppppp",
    "rhbqkbhr"};

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
    unsigned char* local_key = calloc(sizeof(unsigned char),195);

    unsigned char* tempChar = malloc(sizeof(unsigned char)*3);
    int k = 0;
    for(unsigned int i = 0;i<8;i++)
    {
        for(unsigned int j=0;j<8;j++)
        {
            local_key[k++] = chessMatrix[i][j];
            local_key[k++] = i+'0';
            local_key[k++] = j+'0';

            //printf("%s\n", local_key);
        }
    }

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
            chessMatrix[j+1][j+2] = (unsigned char)j;
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
    char pieceValue[7][8]
    ={ "PEGMGEG",
    "P010101",
    "k030405",
    "B030405",
    "R050607",
    "Q091013",
    "K000101"};

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
