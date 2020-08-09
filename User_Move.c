#include "User_Move.h"

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

int validPion(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		pieceCoordonate *pieceToMove) {

	int prevPos = (pieceCurrentPosition->piece == pieceToMove->piece);
	int thisPos = (pieceCurrentPosition->y == (pieceToMove->y - 1))

	return (prevPos && thisPos && (currentMatrix[pieceToMove->y][pieceToMove->x] == '*'));
}

int validPionAttack(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		pieceCoordonate *pieceToMove) {

	int prevPos = (((pieceCurrentPosition->y+1) == pieceToMove->y) && 
					(((pieceCurrentPosition->x+1) == pieceToMove->x) || 
					((pieceCurrentPosition->x-1) == pieceToMove->x)));
	int thisPos = (strchr("PHBRQ",currentMatrix[(pieceToMove->y)][pieceToMove->x]) != 0)

	return (prevPos && thisPos);
}

int validKnight(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		pieceCoordonate *pieceToMove) {

	int valid = (((pieceCurrentPosition->y == (pieceToMove->y + 2)) ||
		(pieceCurrentPosition->y == (pieceToMove->y - 2))) &&
		((pieceCurrentPosition->x == (pieceToMove->x + 1)) ||
			(pieceCurrentPosition->x == (pieceToMove->x - 1))));

	return valid;
}

int validRook(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		pieceCoordonate *pieceToMove) {

	int sgn = -1,i;
	if (strchr("PHBRQ*",currentMatrix[pieceToMove->y][pieceToMove->x]) == 0)
	{
		return 0;
	}

	if (pieceCurrentPosition->x == pieceToMove->x)
	{
		if (pieceCurrentPosition->y < pieceToMove->y)
		{
			sgn = 1;
		}
		i = pieceCurrentPosition->x;
		while(i != pieceToMove->y-sgn) {
			i+=sgn;
			if (currentMatrix[i][pieceToMove->x] != '*')
			{
				return 0;
			}
		}
	}
	else 
		if (pieceCurrentPosition->y == pieceToMove->y)
		{
			if (pieceCurrentPosition->x < pieceToMove->x)
			{
				sgn = 1;
			}
			i = pieceCurrentPosition->y;
			while(i != pieceToMove->x-sgn) {
				i+=sgn;
				if (currentMatrix[pieceToMove->y][i] != '*')
				{
					return 0;
				}
			}
		}
	

	return 1;
}

int validBishop(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		pieceCoordonate *pieceToMove) {

	int sgny = 1,sgnx = 1,i,j;
	if (strchr("PHBRQ*",currentMatrix[pieceToMove->y][pieceToMove->x]) == 0)
	{
		return 0;
	}
	if (pieceCoordonate->y > pieceToMove->y)
	{
		sgny = -1;
	}
	if (pieceCoordonate->x > pieceToMove->x)
	{
		sgnx = -1;
	}
	i = pieceCoordonate->y;
	j = pieceCoordonate->x;
	while (i != pieceToMove->y-sgny) {
		i += sgny;
		j += sgnx;

		if (currentMatrix[i][j] != '*')
		{
			return 0;
		}
	}

	return 1;
}

int validQueen(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		 pieceCoordonate *pieceToMove) {
	return validRook(currentMatrix, pieceCoordonate, pieceToMove) || 
			validBishop(currentMatrix, pieceCoordonate, pieceToMove);
}

int validMove(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		 pieceCoordonate *pieceToMove) {

	if (pieceToMove->piece != currentMatrix[pieceCurrentPosition->y][pieceCurrentPosition->x])
	{
		return 0;
	}

	if (pieceToMove->piece == 'p')
	{
		return (validPion(currentMatrix,pieceCurrentPosition, pieceToMove) || validPionAttack(currentMatrix,pieceCurrentPosition, pieceToMove));
	}

	if (pieceToMove->piece == 'h')
	{
		return validKnight(currentMatrix,pieceCurrentPosition, pieceToMove);
	}

	if (pieceToMove->piece == 'r')
	{
		return validRook(currentMatrix,pieceCurrentPosition, pieceToMove);
	}

	if (pieceToMove->piece == 'b')
	{
		return validBishop(currentMatrix,pieceCurrentPosition, pieceToMove);
	}


	return 1;
}

unsigned char* getPlayerMove(unsigned char* currentKey) {
	unsigned char** currentMatrix = getChessTableFromKey(currentKey);

	pieceCoordonate *pieceToMove = malloc(sizeof(pieceToMove));
	pieceCoordonate *pieceToMovePos = malloc(sizeof(pieceToMove));

	printf("This is the current state of the game:\n");

	printMatrix(currentMatrix);

	printf("Enter your next move\n");
	scanf("%c %d %d ", &(pieceToMoveNow->piece), &(pieceToMoveNow->y), &(pieceToMoveNow->x));
	scanf("%c %d %d ", &(pieceToMove->piece), &(pieceToMove->y), &(pieceToMove->x));

	if (validMove(currentMatrix, pieceToMove))
	{
		return formNewKey(currentMatrix, pieceToMoveNow, pieceToMove);
	}
	printf("Your move is not valid\n");
	return getPlayerMove(currentKey);

}