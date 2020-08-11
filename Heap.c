#include "Heap.h"

Heap* createHeap() {
	Heap *heap = malloc(sizeof(Heap));

	heap->size = 0;
	heap->myHeap = malloc(sizeof(HeapNode *) * 1);

	heap->myHeap[0] = NULL;

	return heap;
}

void heapify(Heap* heap) {
	if(NULL == heap)
		return;

	int k = heap->size - 1, parent;
	HeapNode *aux;

	while(k) {
		parent = (k-1) >> 1;

		if (heap->myHeap[k]->score > heap->myHeap[parent]->score)
		{
			aux = heap->myHeap[k];
			heap->myHeap[k] = heap->myHeap[parent];
			heap->myHeap[parent] = aux; 
		}
		k = parent;
	}
}

void addInHeap(Heap *heap, HeapNode *heapNode) {
	if(NULL == heap)
		return;
	if(NULL == heapNode)
		return;
		
	heap->myHeap = realloc(heap->myHeap, sizeof(HeapNode *) * (heap->size + 1));

	//heap->myHeap[heap->size] = malloc(sizeof(HeapNode *));

	heap->myHeap[heap->size] = heapNode;

	heap->size++;

	heapify(heap);
}

unsigned char* getExtreme(Heap* heap) {
	if(!heap) {
		printf("0 Heap\n");
		return NULL;
	}
	if (!heap->myHeap[0]) {
		printf("heap has no nodes\n");
		printf("%d\n", heap->size);
		return NULL;
	}

	return heap->myHeap[0]->key;
}

void deleteHeap(Heap *heap) {
	if (!heap)
	{
		printf("Heap is null\n");
		return;
	}

	for (int i = 0; i < heap->size; i++)
	{
		free(heap->myHeap[i]->key);
		free(heap->myHeap[i]);
	}

	free(heap->myHeap);

	free(heap);
}