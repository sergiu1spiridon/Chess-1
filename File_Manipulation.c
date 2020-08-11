#include "File_Manipulation.h"

void readFromFile(hashtable *hash) {
    FILE *file;
    file = fopen("myFile", "r");

    if (file == NULL)
    {
        printf("File not found");
        return;
    }

    if(!hash) {
		printf("Hash nonexistent\n");
		return;
	}
    unsigned char *parent = malloc(sizeof(char) * 194);
    while (fscanf(file, "%s", parent) == 1)
    {
        unsigned char *child = malloc(sizeof(char) * 194); 
        
        fscanf(file, "%s\n", child);
        //printf("newRead\n");
        
        //printMatrix(getChessTableFromKey(child));
        //printMatrix(getChessTableFromKey(parent));
        
        addChildToParent(hash, child, parent);

        //printAllHash(hash);

        parent = malloc(sizeof(char) * 194);
    }
    
    free(parent);
    fclose(file);
}

void writeToFile(hashtable *hash) {
    FILE *file;
    file = fopen("myFile", "w");

    if (file == NULL)
    {
        printf("File not found");
        return;
    }

    if(!hash) {
		printf("Hash nonexistent\n");
		return;
	}

	Node *currentNode;
	for (int i = 0; i < hash->size; ++i)
	{	
		currentNode = hash->bucket[i]->head;
		while (currentNode)
		{
			// for (int i = 0; i < currentNode->info->numberOfParents; i++)
			// {
			// 	fprintf(file, "%s %s\n", currentNode->info->parents[i], currentNode->info->key);
			// }

			for (int i = 0; i < currentNode->info->heap->size; i++)
			{
				fprintf(file, "%s %s\n",currentNode->info->key, currentNode->info->heap->myHeap[0]->key);
			}
			currentNode = currentNode->next;
		}
	}

    fclose(file);
}