#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct buckets {
	int numberOfTimesInChecks;
}buckets;

typedef struct hashtable {
	buckets *bucket;
	int size;
	unsigned long (*hashFunction)(unsigned char*);
}hashtable;

unsigned long hash(unsigned char *str);