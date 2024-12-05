
#ifndef GREEDY_H
#define GREEDY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "humanAL.h"
#include "primsAL.h"

extern edge* getMin(humanList*);
extern void greedy_spread(AL*, int, cost*);

#endif