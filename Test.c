#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "LinkedList.h"
#include "Hashtable.h"
#include "common.h"

int main(int argc, char const *argv[])
{
	hashtable *hash = initHashtable(20);

	InfoNode **infoTests = calloc(sizeof(InfoNode), 20);

	infoTests[0] = malloc(sizeof(InfoNode));
	infoTests[0]->key = malloc(sizeof(char) * 1000);

	strcpy(infoTests[0]->key, "abcdefgh");
	infoTests[0]->score = 3;

	infoTests[1] = malloc(sizeof(InfoNode));
	infoTests[1]->key = malloc(sizeof(char) * 1000);

	strcpy(infoTests[1]->key, "abcdefg");
	infoTests[1]->score = 2;

	//printf("%s\n", infoTests[0]->key);

	addToHash(hash, infoTests[0]);
	addToHash(hash, infoTests[1]);

	printf("%d\n", getFromHash(hash, infoTests[0]->key)->info->score);

	deleteHash(hash);

	for (int i = 0; i < 20; ++i)
	{
		if (infoTests[i])
		{
			free(infoTests[i]->key);
			free(infoTests[i]);
		}
	}

	free(infoTests);

	return 0;
}