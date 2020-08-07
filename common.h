#ifndef COMMON
#define COMMON

// general use libraries
#include <stdio.h>
#include <stdlib.h>

//custom made libraries
#include "Hashtable.h"
#include "Linked_List.h"
#include "Heap.h"

typedef struct InfoNode{
    unsigned char* key;
    HeapNode* heap;
}InfoNode;

#endif /* COMMON */