#ifndef LINKED_LIST
#define LINKED_LIST

// general use libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Heap.h"

typedef struct InfoNode{
    unsigned char* key;
    Heap* heap;
    int score;
    unsigned char **parents;
    int numberOfParents;
}InfoNode;

typedef struct Node
{
	InfoNode *info;
	struct Node *next;
}Node;

typedef struct List
{
    Node* head;
    Node* tail;
    int size;
}List;

// create and delete the list
List* createList();
void deleteList(List* currentList);

// manipulate data from front
void push(List* currentList, InfoNode*info);

// manipulate data from rear
void insertRear(List* currentList, InfoNode*info);

// manipulate at index
Node* getElementByKey(List* currentList, unsigned char *key);

#endif /*LINKED_LIST*/