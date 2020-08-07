#ifndef HEAP
#define HEAP

// general use libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//custom made libraries

typedef struct HeapNode{
    unsigned char* key;
    int score;
}HeapNode;

HeapNode* createHeap();

void heapify(HeapNode* heap);

unsigned char* getExtreme(HeapNode* heap);
void addInHeap(HeapNode*heap, HeapNode*heapNode);

#endif /* HEAP */