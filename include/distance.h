#ifndef DISTANCE
#define DISTANCE

#include <stdlib.h>
#include <math.h>
#include "string.h"
#include <cstdio>

#define MFUNC(a,b,c) fmin(fmin(a,b),c)

typedef enum{
    EDIT_DIST,
    HAMMING_DIST
} distanceAlgo;


int editDistance(char*,char*);
int hammingDistance(char*,char*);

#endif