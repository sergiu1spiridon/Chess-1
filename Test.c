#include "common.h"
#include "Heap.h"

int main(int argc, char const *argv[])
{
	Heap *heap = createHeap();

	for (int i = 0; i < 10; ++i)
	{
		HeapNode *nod = malloc(sizeof(HeapNode));
		nod->key = malloc(sizeof(char) * 1000);
		
		//printf("get key: ");
		scanf("%s", nod->key);

		//printf("get score: ");
		scanf("%d", &nod->score);

		addInHeap(heap, nod);
	}

	printf("%s\n", getExtreme(heap));

	deleteHeap(heap);
	return 0;
}