#ifndef COMMON
#define COMMON

// general use libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {false,true}bool;

// get the difference between the current and initial states
int diffStates(unsigned char**currentMatrix);
// get the total number of pieces in game
int countPieces(unsigned char**currentMatrix);

#endif /* COMMON */