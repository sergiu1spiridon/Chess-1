#include "common.h"
#include <time.h>
#include <string.h>
#include "Hashtable.h"
#include "Game_Logic.h"
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
	srand(time(0));

	unsigned char** newMatrix;
	hashtable* hash = initHashtable(100);
	InfoNode * myNode;
	newMatrix = randomMatrix();
	unsigned char* parentKey = (unsigned char*)getKeyFromChessTable(newMatrix);
	Heap* newHeap = createHeap();

	myNode = (InfoNode*)malloc(sizeof(InfoNode));
	myNode->parents = malloc(sizeof(unsigned char *) * 1);
    myNode->numberOfParents = 0;
	myNode->key = parentKey;
	myNode->heap = newHeap;
	myNode->score = getStateScore(parentKey);
	addToHash(hash,myNode);
	

	for(int i=0;i<10;i++)
	{
			newMatrix = randomMatrix();
			unsigned char* key = (unsigned char*)getKeyFromChessTable(newMatrix);
			// unsigned char* key = "aana";
			addChildToParent(hash, key, parentKey);
			// Heap* newHeap = createHeap();

			// myNode = (InfoNode*)malloc(sizeof(InfoNode));

			// myNode->key = key;
			// myNode->heap = newHeap;
			// myNode->score = getStateScore(key);
			// addToHash(hash,myNode);

			printMatrix(getChessTableFromKey(key));
			parentKey = key;
	}
	printAll(hash);

	return 0;
}