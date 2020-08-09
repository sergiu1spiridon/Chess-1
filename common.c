#include "common.h"

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