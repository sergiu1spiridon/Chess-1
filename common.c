#include "common.h"
// print the current matrix
void printMatrix(unsigned char** matrix)
{
		printf("\n\n");
		for(int col = 0;col < 8; col++)
		{
			for(int row = 0;row <8;row ++)
			{
				printf("%c ",matrix[col][row]);
			}
			printf("\n");
		}
		printf("\n\n");
}
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

bool isCheckPlayerFromPawn(unsigned char **currentMatrix, pieceCoordonate *king) {
    return currentMatrix[king->y-1][king->x-1] == 'P' || 
        currentMatrix[king->y-1][king->x+1] == 'P';
}

bool isCheckAIFromPawn(unsigned char **currentMatrix, pieceCoordonate *king) {
    return currentMatrix[king->y+1][king->x+1] == 'p' || 
        currentMatrix[king->y+1][king->x+1] == 'p';
}

bool isCheckFromRook(unsigned char **currentMatrix, pieceCoordonate *king, char c) {
    int sgnx[4] = {0, 1, 0, -1};
    int sgny[4] = {-1, 0, 1, 0};
    int x,y;

    x = king->x;
    y = king->y;

    for (int i = 0; i < 4; i++)
    {
        while(y > 0 && y <7 && x > 0 && x < 7) {
            y += sgny[i];
            x += sgnx[i];
            if (currentMatrix[y][x] != '*')
            {
                if (currentMatrix[y][x] == c)
                {
                    return 1;
                }
                return 0;
            }
        }
    }
    return 0;
}

bool isCheckFromBishop(unsigned char **currentMatrix, pieceCoordonate *king, char c) {
    int sgnx[4] = {-1, -1, 1, 1};
    int sgny[4] = {-1, 1, 1, -1};
    int x,y;

    x = king->x;
    y = king->y;

    for (int i = 0; i < 4; i++)
    {
        while(y > 0 && y <7 && x > 0 && x < 7) {
            y += sgny[i];
            x += sgnx[i];
            if (currentMatrix[y][x] != '*')
            {
                if (currentMatrix[y][x] == c)
                {
                    return 1;
                }
                return 0;
            }
        }
    }
    return 0;
}

bool isCheckFromQueen(unsigned char **currentMatrix, pieceCoordonate *king, char c) {
    int sgnx[8] = {-1, -1, 1, 1, 0, 1, 0, -1};
    int sgny[8] = {-1, 1, 1, -1, -1, 0, 1, 0};
    int x,y;

    x = king->x;
    y = king->y;

    for (int i = 0; i < 8; i++)
    {
        while(y > 0 && y <7 && x > 0 && x < 7) {
            y += sgny[i];
            x += sgnx[i];
            if (currentMatrix[y][x] != '*')
            {
                if (currentMatrix[y][x] == c)
                {
                    return 1;
                }
                return 0;
            }
        }
    }
    return 0;
}

bool isCheckFromKnight(unsigned char **currentMatrix, pieceCoordonate *king, char c) {
    int sgnx[8] = {-2, -2, 2, 2, 1, 1, -1, -1};
    int sgny[8] = {-1, 1, -1, 1, -2, 2, -2, 2};
    int x,y;

    for (int i = 0; i < 8; i++)
    {
            y = king->y + sgny[i];
            x = king->x + sgnx[i];

            if (currentMatrix[y][x] != '*')
            {
                if (currentMatrix[y][x] == c)
                {
                    return 1;
                }
                return 0;
            }
    }
    return 0;
}

bool isNotInCheckPlayer(unsigned char**currentMatrix) {
    pieceCoordonate *king = malloc(sizeof(pieceCoordonate));
    
    for(int i= 0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(currentMatrix[i][j]!='k') 
            {
                king->piece = 'k';
                king->x = j;
                king->y = i;
            }
        }
    }

    bool isFromPawn = isCheckPlayerFromPawn(currentMatrix, king);

    bool isFromRook = isCheckFromRook(currentMatrix, king, 'R');

    bool isFromBishop = isCheckFromBishop(currentMatrix, king, 'B');

    bool isFromQueen = isCheckFromQueen(currentMatrix, king, 'Q');

    bool isFromKnight = isCheckFromKnight(currentMatrix, king, 'H');

    return !(isFromPawn || isFromRook || isFromBishop || isFromQueen || isFromKnight);
}

bool isNotInCheckAI(unsigned char**currentMatrix) {
    pieceCoordonate *king = malloc(sizeof(pieceCoordonate));
    
    for(int i= 0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(currentMatrix[i][j]!='K') 
            {
                king->piece = 'K';
                king->x = j;
                king->y = i;
            }
        }
    }

    bool isFromPawn = isCheckPlayerFromPawn(currentMatrix, king);

    bool isFromRook = isCheckFromRook(currentMatrix, king, 'r');

    bool isFromBishop = isCheckFromBishop(currentMatrix, king, 'r');

    bool isFromQueen = isCheckFromQueen(currentMatrix, king, 'q');

    bool isFromKnight = isCheckFromKnight(currentMatrix, king, 'h');

    return !(isFromPawn || isFromRook || isFromBishop || isFromQueen || isFromKnight);
}