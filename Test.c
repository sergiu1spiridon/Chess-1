#include "Game_Logic.h"

unsigned char** randomMatrix()
{
	unsigned char** matrix = (unsigned char**)malloc(sizeof(unsigned char*)*8);
	for(int i=0;i<8;i++)
	{
			matrix[i] = (unsigned char*)malloc(sizeof(unsigned char)*8);
			for(int j=0;j<8;j++)
			{
					matrix[i][j] = '*';
			}
	}

	const char pieces[] = "PPPPPPPPRHBQKBHRpppppppprhbqkbhr";
	char *newPieces = malloc(sizeof(char)*32);
	int size_newPieces = 0;
	int i=0;
	while(pieces[i+1] != '\0')
	{
		if(rand()%2 == 0)
		{
			newPieces[size_newPieces++] = pieces[i];
		}
		i++;	
		
	}
	newPieces[size_newPieces]='\0';

	i=0;
	while(newPieces[i])
	{
		int col,row;	
		col = rand()%8;
		row = rand()%8;
		while(matrix[col][row]!='*')
		{
			col = rand()%8;
			row = rand()%8;
			
		}
		matrix[col][row] = newPieces[i];
		i++;
	}

	return matrix;

}

int main(int argc, char const *argv[])
{
	// initial chess table
	unsigned char initialChessMatrix[8][8]
  	={  "RHBQKBHR",
		"PPPPPPPP",
		"********",
		"********",
		"********",
		"********",
		"pppppppp",
		"rhbqkbhr"};
	unsigned char** chessMatrix = malloc(sizeof(unsigned char*)*8);
	for(int i=0;i<8;i++)
	{
		chessMatrix[i] = malloc(sizeof(unsigned char)*8);
		strcpy((char*)chessMatrix[i],(const char*)initialChessMatrix[i]);
	}

	//create the hashtable
	hashtable* hash = initHashtable(100);
	InfoNode * myNode;
	unsigned char* parentKey = (unsigned char*)getKeyFromChessTable(chessMatrix);
	Heap* newHeap = createHeap();

	myNode = (InfoNode*)malloc(sizeof(InfoNode));
	myNode->parents = malloc(sizeof(unsigned char *) * 1);
    myNode->numberOfParents = 0;
	myNode->key = parentKey;
	myNode->heap = newHeap;
	myNode->score = getStateScore(parentKey);
	addToHash(hash,myNode);
	
	bool userTurn = rand()%2;
	
	while(true)
	{
		if(userTurn == true)
		{
			chessMatrix = getPlayerMove(chessMatrix);
		}
		else
		{
			chessMatrix = getAIMove(chessMatrix);
		}
		unsigned char* key = (unsigned char*)getKeyFromChessTable(chessMatrix);
		addChildToParent(hash, key, parentKey);

		userTurn = !userTurn;
	}

	printAll(hash);

	return 0;
}