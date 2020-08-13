#include "File_Manipulation.h"
#include "common.h"

void clrscr()
{
    system("@cls||clear");
}

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

int main()
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
	unsigned char** initialChessMatrix2 = malloc(sizeof(unsigned char*)*8);
	for(int i=0;i<8;i++)
	{
		chessMatrix[i] = malloc(sizeof(unsigned char)*8);
		chessMatrix[i] = initialChessMatrix[i];
		initialChessMatrix2[i] = malloc(sizeof(unsigned char)*8);
		initialChessMatrix2[i] = initialChessMatrix[i];
	}

	//create the hashtable
	hashtable* hash = initHashtable(100);
	
	readFromFile(hash);

	//printAllHash(hash);

	InfoNode * myNode;
	
	unsigned char *child;
	unsigned char* parentKey = (unsigned char*)getKeyFromChessTable(initialChessMatrix2);
	
	Heap* newHeap = createHeap();

	myNode = (InfoNode*)malloc(sizeof(InfoNode));
	myNode->parents = malloc(sizeof(unsigned char *) * 1);
    myNode->numberOfParents = 0;
	myNode->key = parentKey;
	myNode->heap = newHeap;
	myNode->score = getStateScore(parentKey);
	
	addToHash(hash,myNode);

	printMatrix(chessMatrix);
	chessMatrix = randomMatrix();

	child = (unsigned char*)getKeyFromChessTable(chessMatrix);
		
	upperLowerChange(&child);
	addChildToParent(hash, child, parentKey);
	parentKey = child;

	printMatrix(chessMatrix);
	//chessMatrix = getPlayerMove(chessMatrix);
	chessMatrix = randomMatrix();
	child = (unsigned char*)getKeyFromChessTable(chessMatrix);
		
	upperLowerChange(&child);
	addChildToParent(hash, child, parentKey);
	parentKey = child;

	printMatrix(chessMatrix);
	//chessMatrix = getPlayerMove(chessMatrix);
	chessMatrix = randomMatrix();

	child = (unsigned char*)getKeyFromChessTable(chessMatrix);
		
	upperLowerChange(&child);
	addChildToParent(hash, child, parentKey);
	parentKey = child;

	//clrscr();
	printf("%d\n", getFromHash(hash, parentKey)->info->score);
	printHeap(getFromHash(hash, parentKey)->info->heap);
	printAllHash(hash);
	writeToFile(hash);


	

	return 0;
}