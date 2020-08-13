#ifndef HASHTABLE
#define HASHTABLE

//custom made libraries
#include "common.h"
#include "Linked_List.h"

typedef struct hashtable {
	List **bucket;
	int size;
	unsigned long (*hashFunction)(unsigned char*);
}hashtable;

unsigned long hash(unsigned char *str);
void addToHash(hashtable *hash, InfoNode *info);
Node *getFromHash(hashtable *hash, unsigned char *key);
hashtable *initHashtable(int size);
void printAll(hashtable *hash);
void deleteHash(hashtable *);

#endif/*HASHTABLE*/