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
		chessMatrix[i] = initialChessMatrix[i];
	}

	//create the hashtable
	hashtable* hash = initHashtable(100);
	
	readFromFile(hash);
	//printAllHash(hash);

	InfoNode * myNode;
	
	unsigned char *child;
	unsigned char* parentKey = (unsigned char*)getKeyFromChessTable(chessMatrix);
	
	Heap* newHeap = createHeap();

	myNode = (InfoNode*)malloc(sizeof(InfoNode));
	myNode->parents = malloc(sizeof(unsigned char *) * 1);
    myNode->numberOfParents = 0;
    //printf("%s\n\n\n", parentKey);
    //upperLowerChange(&parentKey);
    //printf("%s\n", parentKey);
	myNode->key = parentKey;
	myNode->heap = newHeap;
	myNode->score = getStateScore(parentKey);
	
	addToHash(hash,myNode);


	//clrscr();
	
	printf("          ");
	printf("\033[1m%s\033[0m", "Welcome to chess\n");
	srand(time(0));
	bool userTurn = rand()%2;
	
	if(userTurn)
	{
		printf("          ");
		printf("\033[1m%s\033[0m","You will start!\n");
	}
	else
	{
		printf("          ");
		printf("\033[1m%s\033[0m","The computer will start!\n");
		getAIMove(chessMatrix);

		child = (unsigned char*)getKeyFromChessTable(chessMatrix);
		upperLowerChange(&child);
		addChildToParent(hash, child, parentKey);
		parentKey = child;

		userTurn = true;	
	}
	// printf("          ");
	// printf("\033[1m%s\033[0m","Press any key to begin: ");

	// char*str = malloc(sizeof(char)*10);
	// fgets(str,10,stdin);
	// free(str);

	int ok = 0;
	int round = 0;
	while(true)
	{

		if(userTurn == true)
		{
			//isNotInCheckAI(chessMatrix);
			//clrscr();
			printf("          ");
			printf("Game round %d",round++);
			printMatrix(chessMatrix);
			if(!isNotInCheckAI(chessMatrix))
			{
				printf("\n          ");
				printf("Check for AI");
				if(isInCheckMate(chessMatrix))
				{
					printf("\n\n          ");
					printf("Checkmate! Player wins!\n\n");
					break;
				}
			}
			printf("          ");
			printf("If you want to exit, press x");
			chessMatrix = getPlayerMove(chessMatrix);
			if(chessMatrix == NULL)
			{
				break;
			}
			//child = (unsigned char*)getKeyFromChessTable(chessMatrix);
			//upperLowerChange(&child);	

			//addChildToParent(hash, child, parentKey);
			//parentKey = child;

		}
		else
		{		
			ok = 0;
			unsigned char** oldChessMatrix = malloc(sizeof(unsigned char*)*8);
			for(int i=0;i<8;i++)
			{
				oldChessMatrix[i] = malloc(sizeof(unsigned char)*8);
				for(int j=0;j<8;j++)
				{
					oldChessMatrix[i][j]=chessMatrix[i][j];
				}
			}
			if (getFromHash(hash, getKeyFromChessTable(oldChessMatrix)))
			{
				printf("should work\n");
				Node *nod = getFromHash(hash, getKeyFromChessTable(oldChessMatrix));
				unsigned char *heapExtreme = getExtreme(nod->info->heap);
				if(heapExtreme) {
					chessMatrix = getChessTableFromKey(heapExtreme);
					ok = 1;
				}
			}
			if(ok == 0)
			{
			unsigned char** newChessMatrix = getAIMove(chessMatrix);
			if (!isNotInCheckPlayer(newChessMatrix))
			{
				printf("\n          ");
				printf("Check for Player");
			}
			bool isCheck = false;
			for(int i=0;i<8;i++)
			{
				for(int j=0;j<8;j++)
				{
					if(newChessMatrix[i][j]!= oldChessMatrix[i][j])
					{
						isCheck = true;
						i = 8;
						break;

					}
				}
			}	
			if(isCheck == 8)
			{
				printf("\n\n          ");
				printf("Checkmate! Player wins!\n\n");
				break;
			}
			}
		
		}

		child = (unsigned char*)getKeyFromChessTable(chessMatrix);
		upperLowerChange(&child);
		addChildToParent(hash, child, parentKey);
		parentKey = child;
		//printMatrix(getChessTableFromKey(child));

		userTurn = !userTurn;
	}
	writeToFile(hash);

	return 0;
}