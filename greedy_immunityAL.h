#ifndef GREEDY_IMMUNITY_H
#define GREEDY_IMMUNITY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "humanAL.h"

extern edge* getMin_Im(humanList*);
extern void greedy_Im_spread(AL*, int, cost*);

#endif