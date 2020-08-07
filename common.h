#ifndef COMMON
#define COMMON

#include <stdio.h>
#include <stdlib.h>

typedef struct HeapNode{
    unsigned char* key;
    int score;
}HeapNode;

typedef struct InfoNode{
    unsigned char* key;
    // HeapNode* heap;
    int score;
}InfoNode;

HeapNode* createHeap();

void heapify(HeapNode* heap);

unsigned char* getExtreme(HeapNode* heap);
void addInHeap(HeapNode*heap, HeapNode*heapNode);

#endif /* COMMON */