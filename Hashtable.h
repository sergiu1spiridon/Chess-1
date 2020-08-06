#ifndef HASHTABLE
#define HASHTABLE

#include <stdio.h>
#include <stdlib.h>
#include "Linked_List.h"

typedef struct hashtable {
	List **bucket;
	int size;
	unsigned long (*hashFunction)(unsigned char*);
}hashtable;

unsigned long hash(unsigned char *str);
void addToHash(hashtable *hash,unsigned char *key, void *info);
void *getFromHash(hashtable *hash, unsigned char *key);
hashtable initHashtable(int size);

#endif/*HASHTABLE*/