#ifndef HEAP
#define HEAP

#include "common.h"

typedef struct HeapNode{
    unsigned char* key;
    int score;
}HeapNode;

HeapNode* createHeap();

void heapify(HeapNode* heap);

unsigned char* getExtreme(HeapNode* heap);
void addInHeap(HeapNode*heap, HeapNode*heapNode);

#endif /* HEAP */