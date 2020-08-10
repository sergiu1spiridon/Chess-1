#ifndef FILE_MANIPULATION
#define FILE_MANIPULATION

// general use libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFromFile(hashtable *hash);

void writeToFile(unsigned char *parentKey, unsigned char *childKey);

#endif /* FILE_MANIPULATION */