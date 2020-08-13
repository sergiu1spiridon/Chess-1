#include "Heap.h"

Heap* createHeap() {
	Heap *heap = malloc(sizeof(Heap));

	heap->size = 0;
	heap->myHeap = malloc(sizeof(HeapNode *) * 1);

	heap->myHeap[0] = NULL;

	return heap;
}

void printHeap(Heap *heap) {
	for(int i = 0; i < heap->size; i++) {
		printf("%d ", heap->myHeap[i]->score);
	}
	printf("\n");
}

void heapifyFromPos(Heap *heap, unsigned char *key,int score) {
	int i;

	for(i = 0; i < heap->size; i++) {
		if (strcmp((char *)(heap->myHeap[i]->key), (char *)key) == 0)
		{
			break;
		}
	}

	int k = i;
	heap->myHeap[k]->score += score;
	
	int left = ((k + 1) << 1) - 1, right = ((k + 1) << 1);
	HeapNode *aux;

	while(left < heap->size) {
		left = ((k + 1) << 1) - 1;
		right = ((k + 1) << 1);
		if(right >= heap->size || heap->myHeap[left]->score > heap->myHeap[right]->score) {

			if (heap->myHeap[left]->score > heap->myHeap[k]->score)
			{
				aux = heap->myHeap[k];
				heap->myHeap[k] = heap->myHeap[left];
				heap->myHeap[left] = aux;
				k = left;
			}
			else
				break;
		}
		else {
			if (right < heap->size && heap->myHeap[right]->score > heap->myHeap[k]->score)
			{
				aux = heap->myHeap[k];
				heap->myHeap[k] = heap->myHeap[right];
				heap->myHeap[right] = aux;
				k = right;
			}
			else
				break;
		}
	}

	k = i;

	int parent;

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