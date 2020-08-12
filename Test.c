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


	//clrscr();
	
	printf("          ");
	printf("Welcome to chess\n");
	srand(time(0));
	bool userTurn = true;
	
	if(userTurn)
	{
		printf("          ");
		printf("You will start!\n");
	}
	else
	{
		printf("          ");
		printf("The computer will start!\n");
		//printf("%s\n", (const char*)getKeyFromChessTable(chessMatrix));


		chessMatrix = (getAIMove(chessMatrix));
		
		printMatrix(chessMatrix);
		printf("\n\n          ");
		printf("Computer Turn. Press any key to continue...");
		getc(stdin);

		child = (unsigned char*)getKeyFromChessTable(chessMatrix);
		upperLowerChange(&child);
		//if(strcmp((char *)child, (char *)parentKey))
		addChildToParent(hash, child, parentKey);

		parentKey = child;

		userTurn = true;	
	}

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
			if(!isNotInCheckPlayer(chessMatrix))
			{
				printf("\n          ");
				printf("Check for AI");

				if(isInCheckMate(chessMatrix))
				{
					printf("\n\n          ");
					printf("Checkmate! AI wins!\n\n");
					break;
				}
			}
			printf("          ");
			printf("If you want to exit, press x");
			chessMatrix = getPlayerMove(chessMatrix);
			if(chessMatrix == NULL)
			{
				writeToFile(hash);
				return 1;
			}
			//child = (unsigned char*)getKeyFromChessTable(chessMatrix);
			//upperLowerChange(&child);	

			//addChildToParent(hash, child, parentKey);
			//parentKey = child;

		}
		else
		{		
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
				Node *nod = getFromHash(hash, getKeyFromChessTable(oldChessMatrix));
				unsigned char *heapExtreme = getExtreme(nod->info->heap);
				if(heapExtreme) {
					chessMatrix = getChessTableFromKey(heapExtreme);
				}
				else
				{
					chessMatrix = getAIMove(chessMatrix);
				}
			}
			else
			{
				chessMatrix = getAIMove(chessMatrix);
			}

			printMatrix(chessMatrix);
			printf("\n\n          ");
			printf("Computer Turn. Press any key to continue...");

			if (!isNotInCheckAI(chessMatrix))
			{
				printf("\n          ");
				printf("Check for Player");
				//is checkmate for Player?
				if(matrixCmp(chessMatrix,oldChessMatrix)==0)
				{
					printf("\n\n          ");
					printf("Checkmate! Player wins!\n\n");
					break;
				}
				
			}
			getc(stdin);
			getc(stdin);

			
		
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