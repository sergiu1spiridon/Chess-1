#ifndef HASHTABLE
#define HASHTABLE

#include <stdio.h>
#include <stdlib.h>

typedef struct buckets {
	int numberOfTimesInCheck;
}buckets;

typedef struct hashtable {
	buckets *bucket;	
}hashtable;
#endif/*HASHTABLE*/