#include "Game_Logic.h"


// get the key for the hashtable from the current state
unsigned char* getKeyFromChessTable(unsigned char**chessMatrix)
{
    unsigned char* local_key = calloc(sizeof(unsigned char),193);

    int k = 0;
    for(unsigned int i = 0;i<8;i++)
    {
        for(unsigned int j=0;j<8;j++)
        {
            local_key[k++] = chessMatrix[i][j];
            local_key[k++] = i+'0';
            local_key[k++] = j+'0';

            //printf("%s\n", local_key);
        }
    }
    local_key[192] = '\0';
    return local_key;
}
// get the current state from the hashtable
unsigned char** getChessTableFromKey(unsigned char* key)
{
    unsigned char ** chessMatrix = malloc(sizeof(unsigned char*)*8);
    
    for(int i= 0;i<8;i++)
    {
        chessMatrix[i] = malloc(sizeof(unsigned char)*8);
    }
    for(int j=0;j<192;j+=3)
    {
        chessMatrix[key[j+1]-'0'][key[j+2]-'0'] = (unsigned char)key[j];
    }
    return chessMatrix;
}
// get the score of the state from the key of the table
int getStateScore(unsigned char *chessMatrixKey) {
    if( NULL == chessMatrixKey)
    {
        return -1;
    }

    unsigned char** matrix = getChessTableFromKey(chessMatrixKey);

    int result = 0;

    int pieceValue[6][3] = {{1,1,1},{3,4,5},{3,4,5},{5,6,7},{9,10,13},{0,1,1}};

    int diffCount = diffStates(matrix);
    int totalPieces = countPieces(matrix);

    // early game is defined as diffCount < 16
    // middle game is defined as diffCount >= 16 and total pieces >=8
    // end game is otherwise
    int typeGame;
    if(diffCount < 16)
    {
        //early game
        typeGame = 0;
    }
    else if(diffCount >=16 && totalPieces >=8)
    {
        //middle game
        typeGame = 1;
    }
    else
    {
        //end game
        typeGame = 2;
    } 

    //calculate the result
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            switch (matrix[i][j])
            {
            case 'P':
                result += pieceValue[0][typeGame];
                break;
            case 'H':
                result += pieceValue[1][typeGame];
                break;
            case 'B':
                result += pieceValue[2][typeGame];
                break;
            case 'R':
                result += pieceValue[3][typeGame];
                break;
            case 'Q':
                result += pieceValue[4][typeGame];
                break;
            case 'K':
                result += pieceValue[5][typeGame];
                break;
            case 'p':
                result -= pieceValue[0][typeGame];
                break;
            case 'h':
                result -= pieceValue[1][typeGame];
                break;
            case 'b':
                result -= pieceValue[2][typeGame];
                break;
            case 'r':
                result -= pieceValue[3][typeGame];
                break;
            case 'q':
                result -= pieceValue[4][typeGame];
                break;
            case 'k':
                result -= pieceValue[5][typeGame];
                break;
            default:
                break;
            }
        }
        //free(matrix[i]);
    }
    free(matrix);

    return result;
}

void printAllHash(hashtable *hash) {
    if(!hash) {
        printf("Hash nonexistent\n");
        return;
    }
    Node *currentNode;
    int nr;
    for (int i = 0; i < hash->size; i++)
    {   
        currentNode = hash->bucket[i]->head;
        while (currentNode)
        {
            nr = 0;
            printf("in bucket[%d] number %d is %s", i, nr, 
                currentNode->info->key);

            printMatrix(getChessTableFromKey(currentNode->info->key));

            printf("its parents are:\n");
            for (int j = 0; j < currentNode->info->numberOfParents; j++)
            {
                printMatrix(getChessTableFromKey(currentNode->info->parents[j]));
            }

            printf("its children are:\n");
            for (int j = 0; j < currentNode->info->heap->size; j++)
            {
                printMatrix(getChessTableFromKey(currentNode->info->heap->myHeap[j]->key));
            }
            currentNode = currentNode->next;
            nr++;
        }
    }
}

int addChildToParent(hashtable *hash, unsigned char* chessMatrixKey, unsigned char* parentKey)
{
    // printAllHash(hash);
    Node *nodeForKey = getFromHash(hash, chessMatrixKey);

    if(nodeForKey == NULL) {
        //printf("cant find it\n");
        InfoNode *newNode = malloc(sizeof(InfoNode));

        newNode->key = chessMatrixKey;
        newNode->score = getStateScore(chessMatrixKey);
        newNode->parents = malloc(sizeof(unsigned char *) * 1);
        newNode->numberOfParents = 1;
        newNode->parents[0] = parentKey;
        Heap* newHeap = createHeap();
        newNode->heap = newHeap;

        HeapNode *newHeapNode = malloc(sizeof(HeapNode));

        newHeapNode->key = chessMatrixKey;
        newHeapNode->score = newNode->score;
        
        if (getFromHash(hash, parentKey) == NULL)
        {
            //printf("%s\n", getFromHash(hash, parentKey));
            //printf("Returns null\n");
            InfoNode *newParent = malloc(sizeof(InfoNode));

            newParent->key = parentKey;
            newParent->score = getStateScore(parentKey);
            newParent->parents = malloc(sizeof(unsigned char *) * 1);
            newParent->numberOfParents = 0;
            newParent->parents[0] = NULL;
            Heap* newHeapP = createHeap();
            newParent->heap = newHeapP;

            addToHash(hash, newParent);

            if (!getFromHash(hash, parentKey))
                printf("still null hash\n");
            
        }
        addInHeap(getFromHash(hash, parentKey)->info->heap, newHeapNode);

        addToHash(hash, newNode);
        //printAllHash(hash);
        //printf("%s\n", getFromHash(hash, chessMatrixKey)->info->key);
    } else {
        //printf("intra in else\n");
        //printMatrix(getChessTableFromKey(nodeForKey->info->key));
         InfoNode *newNode = nodeForKey->info;
         for (int i = 0; i < newNode->numberOfParents; i++)
         {
             if (strcmp((char *)newNode->parents[i],(char *)parentKey) == 0)
             {
                printMatrix(getChessTableFromKey(newNode->parents[i]));
                printMatrix(getChessTableFromKey(parentKey));
                 return 0;
             }
             
         }
         
        newNode->parents = realloc(newNode->parents, sizeof(unsigned char *) * (newNode->numberOfParents+1));
        newNode->parents[newNode->numberOfParents] = parentKey;
        newNode->numberOfParents ++;

        HeapNode *newHeapNode = malloc(sizeof(HeapNode));

        newHeapNode->key = chessMatrixKey;
        newHeapNode->score = newNode->score;
        
        Node *parinteHashNod = getFromHash(hash, parentKey); 
        
        if (!parinteHashNod)
        {
            // printf("parinte not found\n");
            InfoNode *newParent = malloc(sizeof(InfoNode));

            newParent->key = parentKey;
            newParent->score = getStateScore(parentKey);
            newParent->parents = malloc(sizeof(unsigned char *) * 1);
            newParent->numberOfParents = 0;
            newParent->parents[0] = NULL;
            Heap* newHeapP = createHeap();
            newParent->heap = newHeapP;

            addToHash(hash, newParent);
        }

         InfoNode *currentNode = getFromHash(hash, parentKey)->info;

         addInHeap(currentNode->heap, newHeapNode);
         
         Node *currentParent;
         
         List *myQueue = createList();
         
         insertRear(myQueue, currentNode);
         printAllHash(hash);
         while ((myQueue->size) != 0)
         {
            // printf("intra in while size: %d \n", myQueue->size);
             currentNode = popList(myQueue);
            printf("intra in while size: %d \n", myQueue->size);
             printf("%s\n", currentNode->key);
             
             newHeapNode->key = currentNode->key;

             newHeapNode->score = currentNode->score;
             
             for (int i = 0; i < currentNode->numberOfParents; i++)
             {
               printf("%d\n", currentNode->numberOfParents);
               currentParent = getFromHash(hash,currentNode->parents[i]);
               printf("gasit parinte:\n");
               printMatrix(getChessTableFromKey(currentParent->info->key));
               currentParent->info->score += newNode->score;
               
               addInHeap(currentParent->info->heap, newHeapNode);
               insertRear(myQueue, currentParent->info);
             }
         }
         
         
    }
    return 0;
}

unsigned char* getNextMove(hashtable *hash, unsigned char* currentMoveKey) {
	Node *currentNode = getFromHash(hash, currentMoveKey);

	return getExtreme(currentNode->info->heap);
}

void upperLowerChange(unsigned char **key) {
    int i = 0;
    char *digits = {"0,1,2,3,4,5,6,7,8,9,*"};
    //printf("%s\n\n\n", *key);
    while((*key)[i] != '\0') {
        if(strchr(digits, (*key)[i]) == NULL) {

        if((*key)[i] < 'a') {
            (*key)[i] += 32;
            (*key)[i + 1] = (7 - ((*key)[i + 1] - '0')) + '0';
        } 
        else if((*key)[i] > 'a') {
            (*key)[i] -= 32;
            (*key)[i + 1] = (7 - ((*key)[i + 1] - '0')) + '0';
        }

        }
        else
            if ((*key)[i] == '*')
            {
                (*key)[i + 1] = (7 - ((*key)[i + 1] - '0')) + '0';
            }

        i++;
    }
    *key = getKeyFromChessTable(getChessTableFromKey(*key));
    //printf("%s\n\n\n", *key);
}
