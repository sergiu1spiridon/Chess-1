#include "common.h"
//print colored matrix if on UNIX
#ifdef _WIN32 // Includes both 32 bit and 64 bit
        #ifdef _WIN64
            #define COLOR ""
            #define ENDING_COLOR printf("| ");
        #else 
            #define COLOR ""
            #define ENDING_COLOR printf("| ");
        #endif
    #else
        #define COLOR "\033[0;31m"
        #define ENDING_COLOR printf("\033[0m| ");
    #endif
int matrixCmp(unsigned char**firstMatrix, unsigned char**secondMatrix)
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(firstMatrix[i][j]<secondMatrix[i][j])
                return -1;
            if(firstMatrix[i][j]>secondMatrix[i][j])
                return 1;
        }
    }
    return 0;
}
// print the current matrix
void printMatrix(unsigned char** matrix)
{
	printf("\n");
    printf("          ");
    printf("  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7");
    printf("\n          ");
    printf("-----------------------------------\n");
	for(int col = 0;col < 8; col++)
	{
        printf("          ");
        printf("%d | ",col);
		for(int row = 0;row <8;row ++)
		{
            if(matrix[col][row]=='*')
                printf("  | ");
            else
            {   
                if(matrix[col][row]<'a')
                {
                    printf(COLOR);
                }
			    printf("%c ",matrix[col][row]);
                ENDING_COLOR
            }
		}
        printf("\n          ");
		printf("-----------------------------------\n");
	}
	printf("\n");
}
// get the difference between the current and initial states
int diffStates(unsigned char**currentMatrix)
{
    NULL_PARAM_STRUCT_VALIDATION(currentMatrix)

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
    NULL_PARAM_STRUCT_VALIDATION(currentMatrix)

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

    NULL_PARAM_STRUCT_VALIDATION(currentMatrix)
    NULL_PARAM_STRUCT_VALIDATION(king)

    if(king->y-1 < 0)
        return 0;
    if(king->x-1 < 0)
        return currentMatrix[king->y-1][king->x+1] == 'P';
    if(king->x+1 > 7)
        return currentMatrix[king->y-1][king->x-1] == 'P';

    return (currentMatrix[king->y-1][king->x-1] == 'P' || 
        currentMatrix[king->y-1][king->x+1] == 'P');
}

bool isCheckAIFromPawn(unsigned char **currentMatrix, pieceCoordonate *king) {
    NULL_PARAM_STRUCT_VALIDATION(currentMatrix)
    NULL_PARAM_STRUCT_VALIDATION(king)

    if(king->y+1 < 0)
        return 0;
    if(king->x-1 < 0)
        return currentMatrix[king->y+1][king->x+1] == 'p';
    if(king->x+1 > 7)
        return currentMatrix[king->y+1][king->x-1] == 'p';
    return (currentMatrix[king->y+1][king->x-1] == 'p' || 
        currentMatrix[king->y+1][king->x+1] == 'p');
}

bool isCheckFromRook(unsigned char **currentMatrix, pieceCoordonate *king, char c) {
    NULL_PARAM_STRUCT_VALIDATION(currentMatrix)
    NULL_PARAM_STRUCT_VALIDATION(king)

    int sgnx[4] = {0, 1, 0, -1};
    int sgny[4] = {-1, 0, 1, 0};
    int x,y;

    for (int i = 0; i < 4; i++)
    {
        y = king->y + sgny[i];
        x = king->x + sgnx[i];
        while(y >= 0 && y <= 7 && x >= 0 && x <= 7) {
            
            if (currentMatrix[y][x] != '*')
            {
                if (currentMatrix[y][x] == c)
                {
                    return 1;
                }
                break;
            }
            y += sgny[i];
            x += sgnx[i];
        }
    }
    return 0;
}

bool isCheckFromBishop(unsigned char **currentMatrix, pieceCoordonate *king, char c) {
    NULL_PARAM_STRUCT_VALIDATION(currentMatrix)
    NULL_PARAM_STRUCT_VALIDATION(king)

    int sgnx[4] = {-1, -1, 1, 1};
    int sgny[4] = {-1, 1, 1, -1};
    int x,y;

    for (int i = 0; i < 4; i++)
    {
        x = king->x + sgnx[i];
        y = king->y + sgny[i];
        
        while(y >= 0 && y <= 7 && x >= 0 && x <= 7) {

            if (currentMatrix[y][x] != '*')
            {
                if (currentMatrix[y][x] == c)
                {
                    return 1;
                }
                break;
            }
            y += sgny[i];
            x += sgnx[i];
        }
    }
    return 0;
}

bool isCheckFromQueen(unsigned char **currentMatrix, pieceCoordonate *king, char c) {
    NULL_PARAM_STRUCT_VALIDATION(currentMatrix)
    NULL_PARAM_STRUCT_VALIDATION(king)

    int sgnx[8] = {-1, -1, 1, 1, 0, 1, 0, -1};
    int sgny[8] = {-1, 1, 1, -1, -1, 0, 1, 0};
    int x,y;

    

    for (int i = 0; i < 8; i++)
    {
        x = king->x + sgnx[i];
        y = king->y + sgny[i];

        while(y >= 0 && y <= 7 && x >= 0 && x <= 7) {
            
            if (currentMatrix[y][x] != '*')
            {
                if (currentMatrix[y][x] == c)
                {
                    return 1;
                }
                break;
            }
            y += sgny[i];
            x += sgnx[i];
        }
    }
    return 0;
}

bool isCheckFromKnight(unsigned char **currentMatrix, pieceCoordonate *king, char c) {
    NULL_PARAM_STRUCT_VALIDATION(currentMatrix)
    NULL_PARAM_STRUCT_VALIDATION(king)

    int sgnx[8] = {-2, -2, 2, 2, 1, 1, -1, -1};
    int sgny[8] = {-1, 1, -1, 1, -2, 2, -2, 2};
    int x,y;

    for (int i = 0; i < 8; i++)
    {
            y = king->y + sgny[i];
            x = king->x + sgnx[i];
            if (y > 7 || y < 0 || x > 7 || x < 0)
            {
                continue;
            }
            if (currentMatrix[y][x] == c)
            {
                return 1;
            }
            
    }
    return 0;
}

bool isNotInCheckPlayer(unsigned char**currentMatrix) {
    NULL_PARAM_STRUCT_VALIDATION(currentMatrix)

    pieceCoordonate *king = malloc(sizeof(pieceCoordonate));
    
    for(int i= 0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(currentMatrix[i][j]=='k') 
            {
                king->piece = 'k';
                king->x = j;
                king->y = i;
            }
        }
    }
    
    NULL_PARAM_STRUCT_VALIDATION(king)

    bool isFromPawn = isCheckPlayerFromPawn(currentMatrix, king);

    bool isFromRook = isCheckFromRook(currentMatrix, king, 'R');

    bool isFromBishop = isCheckFromBishop(currentMatrix, king, 'B');

    bool isFromQueen = isCheckFromQueen(currentMatrix, king, 'Q');

    bool isFromKnight = isCheckFromKnight(currentMatrix, king, 'H');

    return !(isFromPawn || isFromRook || isFromBishop || isFromQueen || isFromKnight);
}

bool isNotInCheckAI(unsigned char**currentMatrix) {
    
    NULL_PARAM_STRUCT_VALIDATION(currentMatrix)

    pieceCoordonate *king = malloc(sizeof(pieceCoordonate));
    
    for(int i= 0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(currentMatrix[i][j]=='K') 
            {
                king->piece = 'K';
                king->x = j;
                king->y = i;
            }
        }
    }

    NULL_PARAM_STRUCT_VALIDATION(king)

    bool isFromPawn = isCheckAIFromPawn(currentMatrix, king);

    bool isFromRook = isCheckFromRook(currentMatrix, king, 'r');

    bool isFromBishop = isCheckFromBishop(currentMatrix, king, 'b');

    bool isFromQueen = isCheckFromQueen(currentMatrix, king, 'q');

    bool isFromKnight = isCheckFromKnight(currentMatrix, king, 'h');

    bool result = !(isFromPawn || isFromRook || isFromBishop || isFromQueen || isFromKnight);
    return result;
}