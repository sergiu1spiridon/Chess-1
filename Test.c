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
	char *newPieces;
	int i=0;
	while(pieces[i+1] != '\0')
	{
		if(rand()%2 == 0)
		{
			newPieces[strlen(newPieces)+1] = pieces[i];
		}
		i++;	
		
	}
	printf("%s\n", pieces);
	i=0;
	while(pieces[i])
	{
		int col,row;	
		col = rand()%8;
		row = rand()%8;
		printMatrix(matrix);
		while(matrix[col][row]!='*')
		{
			printf("%d %d %c\n",col,row,matrix[col][row]);
			col = rand()%8;
			row = rand()%8;
			
		}
		matrix[col][row] = pieces[i];
		*(pieces+i)=*(&(pieces[i+1]));
	}

	return matrix;

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