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

void printHeap(Heap *heap);

void heapify(Heap*heap);

void heapifyFromPos(Heap *heap, unsigned char *key, int score);

unsigned char* getExtreme(Heap*heap);
void addInHeap(Heap *heap, HeapNode *heapNode);

void deleteHeap(Heap*heap);

#endif /* HEAP */