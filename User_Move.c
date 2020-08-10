#include "User_Move.h"

int validPion(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		pieceCoordonate *pieceToMove) {

	int prevPos = (pieceCurrentPosition->piece == pieceToMove->piece);
	int thisPos = (pieceCurrentPosition->y == (pieceToMove->y + 1) 
		|| ((pieceCurrentPosition->y == (pieceToMove->y + 2)) && pieceCurrentPosition->y == 6))
		&& (pieceCurrentPosition->x == pieceToMove->x);

	return (prevPos && thisPos && (currentMatrix[pieceToMove->y][pieceToMove->x] == '*'));
}

int validPionAttack(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		pieceCoordonate *pieceToMove) {

	int prevPos = (((pieceCurrentPosition->y-1) == pieceToMove->y) && 
					(((pieceCurrentPosition->x+1) == pieceToMove->x) || 
					((pieceCurrentPosition->x-1) == pieceToMove->x)));
	int thisPos = (strchr("PHBRQ",currentMatrix[(pieceToMove->y)][pieceToMove->x]) != NULL);

	return (prevPos && thisPos);
}

int validKnight(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		pieceCoordonate *pieceToMove) {
	if (strchr("PHBRQ*",currentMatrix[pieceToMove->y][pieceToMove->x]) == NULL)
	{
		return 0;
	}
	int valid1 = (((pieceCurrentPosition->y == (pieceToMove->y + 2)) ||
		(pieceCurrentPosition->y == (pieceToMove->y - 2))) &&
		((pieceCurrentPosition->x == (pieceToMove->x + 1)) ||
			(pieceCurrentPosition->x == (pieceToMove->x - 1))));

	int valid2 = (((pieceCurrentPosition->y == (pieceToMove->y + 1)) ||
		(pieceCurrentPosition->y == (pieceToMove->y - 1))) &&
		((pieceCurrentPosition->x == (pieceToMove->x + 2)) ||
			(pieceCurrentPosition->x == (pieceToMove->x - 2))));

	return valid1 || valid2;
}

int validRook(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		pieceCoordonate *pieceToMove) {

	int sgn = -1,i;
	if (strchr("PHBRQ*",currentMatrix[pieceToMove->y][pieceToMove->x]) == NULL)
	{
		return 0;
	}

	if (pieceCurrentPosition->x == pieceToMove->x)
	{
		if (pieceCurrentPosition->y < pieceToMove->y)
		{
			sgn = 1;
		}
		i = pieceCurrentPosition->y;
		while(i != pieceToMove->y-sgn) {
			i+=sgn;
			if (i > 7 || i < 0)
			{
				return 0;
			}
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
			i = pieceCurrentPosition->x;
			while(i != pieceToMove->x-sgn) {
				i+=sgn;
				
				if (i > 7 || i < 0)
				{
					return 0;
				}

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
	if (strchr("PHBRQ*",currentMatrix[pieceToMove->y][pieceToMove->x]) == NULL)
	{
		return 0;
	}
	if (pieceCurrentPosition->y > pieceToMove->y)
	{
		sgny = -1;
	}
	if (pieceCurrentPosition->x > pieceToMove->x)
	{
		sgnx = -1;
	}
	i = pieceCurrentPosition->y;
	j = pieceCurrentPosition->x;
	while (i != pieceToMove->y-sgny) {
		i += sgny;
		j += sgnx;
		if (i > 7 || i < 0 || j > 7 || j < 0)
		{
			return 0;
		}

		if (currentMatrix[i][j] != '*')
		{
			return 0;
		}

	}
	i += sgny;
	j += sgnx;
	
	if (i == pieceToMove->y && j == pieceToMove->x)
	{
		return 1;
	}
	return 0;
}

int validQueen(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		 pieceCoordonate *pieceToMove) {
	if (strchr("PHBRQ*",currentMatrix[pieceToMove->y][pieceToMove->x]) == NULL)
	{
		return 0;
	}
	return validRook(currentMatrix, pieceCurrentPosition, pieceToMove) || 
			validBishop(currentMatrix, pieceCurrentPosition, pieceToMove);
}

int validKing(unsigned char **currentMatrix,pieceCoordonate *pieceCurrentPosition,
		 pieceCoordonate *pieceToMove) {
	if (strchr("PHBRQ*",currentMatrix[pieceToMove->y][pieceToMove->x]) == NULL)
	{
		return 0;
	}
	if ((((pieceCurrentPosition->x - pieceToMove->x) > 1) || 
		((pieceCurrentPosition->x - pieceToMove->x) < -1))
			&& (((pieceCurrentPosition->y - pieceToMove->y) > 1) || 
				((pieceCurrentPosition->y - pieceToMove->y) < -1))) {
		return 0;
	}
	return 1;
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

unsigned char** getPlayerMove(unsigned char** currentMatrix) {

	pieceCoordonate *pieceToMove = malloc(sizeof(pieceCoordonate));
	pieceCoordonate *pieceToMovePos = malloc(sizeof(pieceCoordonate));

	printf("\n          ");
	printf("Enter your next move!");
	printf("\n          ");
	printf("Current location: ");
	
	char command;
	scanf("\n%c", &command);
	if (command == 'x')
	{
		printf("\n          ");
		printf("Thank you for playing!\n\n");
		return NULL;
	}
	else
	{
		pieceToMovePos->y = (int)(command -'0');
	}

	scanf("%d", &pieceToMovePos->x);

	pieceToMovePos->piece = currentMatrix[pieceToMovePos->y][pieceToMovePos->x];
	pieceToMove->piece = pieceToMovePos->piece;

	printf("          ");
	printf("    New location: ");
	scanf("%d %d", &pieceToMove->y, &pieceToMove->x);

	if (validMove(currentMatrix,pieceToMovePos, pieceToMove)&&
		strchr("RBRKQP*",pieceToMovePos->piece)==NULL)
	{
		unsigned char** nextMatrix = malloc(sizeof(unsigned char*) * 8); 
    	for(int i=0;i<8;i++)
    	{
        	nextMatrix[i] = malloc(sizeof(unsigned char)*8);
        	memcpy(nextMatrix[i],currentMatrix[i],8);
    	}
		

		nextMatrix[pieceToMovePos->y][pieceToMovePos->x] = '*';
		nextMatrix[pieceToMove->y][pieceToMove->x] = pieceToMove->piece;

		if (isNotInCheckPlayer(nextMatrix))
		{
			free(currentMatrix);
			return nextMatrix;
		}
	}
	printf("Your move is not valid\n");
	free(pieceToMovePos);
	free(pieceToMove);
	return getPlayerMove(currentMatrix);

}