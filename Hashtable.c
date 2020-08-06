#include "Hashtable.h"
#include "LinkedList.h"

unsigned long
hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

void addToHash(hashtable *hash, void *info) {
	unsigned long indexOfElement = hash->hashFunction(info->key) % hash->size;

	push(hash->bucket[indexOfElement], info);
}

Node *getFromHash(hashtable *hash, unsigned char *key) {
	unsigned long indexOfElement = hash->hashFunction(key) % hash->size;

	return getElementBykey(hash[indexOfElement], key);
}

hashtable initHashtable(int size) {
	hashtable *hash = malloc(sizeof(hashtable));

	if (!hash)
	{
		printf("Hash not formed correctly\n");
		return NULL;
	}

	hash->bucket = malloc(sizeof(List *) * size);

	if(hash->bucket == NULL) {
		printf("Buckets not formed correctly\n");
		return NULL;
	}

	for (int i = 0; i < size; i++) {
		(hash->bucket + i) = (hash->bucket + i - 1) + sizeof(List*);

		hash->bucket[i]->head = NULL;
		hash->bucket[i]->tail = NULL;
		hash->bucket[i]->size = 0;
	}

	return hash;
}