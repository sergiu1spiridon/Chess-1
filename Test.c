#include "common.h"
#include <time.h>
#include <string.h>
#include "Hashtable.h"
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

	char pieces[] = "PPPPPPPPRHBQKBHRpppppppprhbqkbhr";

	int i=0;
	while(pieces[i])
	{
		if(rand()%2 == 0)
		{
			strncpy(pieces+i,pieces+i+1,strlen(pieces+i));
		}
		i++;
	}

	i=0;
	while(pieces[i])
	{
		int col,row;	
		col = rand()%8;
		row = rand()%8;
		while(matrix[col][row]!='*')
		{
			col = rand()%8;
			row = rand()%8;
			
		}
		matrix[col][row] = pieces[i];
		strncpy(pieces+i,pieces+i+1,strlen(pieces+i));
	}

	return matrix;

}
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
int main(int argc, char const *argv[])
{
	srand(time(0));

	unsigned char** newMatrix;

	for(int i=0;i<10;i++)
	{
			newMatrix = randomMatrix();
			printMatrix(newMatrix);
			unsigned char* key = (unsigned char*)getKeyFromChessTable(newMatrix);

			Heap* newHeap = createHeap();

			InfoNode * myNode = (InfoNode*)malloc(sizeof(InfoNode));
			//myNode->key = malloc(sizeof(char) * 192);

			printf("%s\n", key);

			myNode->key = key;
			myNode->heap = newHeap;

			hashtable* hash = initHashtable(100);

			addToHash(hash,myNode);

			printMatrix(getChessTableFromKey(key));
			
	}
	

	return 0;
}