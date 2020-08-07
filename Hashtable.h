#ifndef HASHTABLE
#define HASHTABLE

#include "common.h"

typedef struct hashtable {
	List **bucket;
	int size;
	unsigned long (*hashFunction)(unsigned char*);
}hashtable;

unsigned long hash(unsigned char *str);
void addToHash(hashtable *hash, InfoNode *info);
Node *getFromHash(hashtable *hash, unsigned char *key);
hashtable *initHashtable(int size);
void deleteHash(hashtable *);

#endif/*HASHTABLE*/