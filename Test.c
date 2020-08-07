#include "common.h"
#include "Game_Logic.h"

unsigned char *pieceValue[8]

={ "PEGMGEG",
"P010101",
"k030405",
"B030405",
"R050607",
"Q091013",
"K000101"};

/*
 * Initial chess matrix
*/
unsigned char *initialChessMatrix[8]
  ={"RkBQKBkR",
    "PPPPPPPP",
    "********",
    "********",
    "********",
    "********",
    "PPPPPPPP",
    "RkBQKBkR"};


int main(int argc, char const *argv[])
{

	unsigned char* key = (unsigned char*)getKeyFromChessTable(initialChessMatrix);
	Heap* newHeap = createHeap();

	InfoNode * myNode = malloc(sizeof(InfoNode));
	//myNode->key = malloc(sizeof(char) * 192);

	printf("%s\n", key);

	myNode->key = key;
	myNode->heap = newHeap;

	hashtable* hash = initHashtable(100);

	addToHash(hash,myNode);

	return 0;
}