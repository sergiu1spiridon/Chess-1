#ifndef HEAP
#define HEAP

// general use libraries
#include "common.h"

//custom made libraries

typedef struct HeapNode {
    unsigned char* key;
    int score;
}HeapNode;

typedef struct Heap {
	int size;
	HeapNode **myHeap;
}Heap;

Heap* createHeap();

void heapify(Heap*heap);

unsigned char* getExtreme(Heap*heap);
void addInHeap(Heap *heap, HeapNode *heapNode);

void deleteHeap(Heap*heap);

#endif /* HEAP */