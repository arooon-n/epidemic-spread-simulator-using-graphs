#ifndef DIJKSTRAAL_H
#define DIJKSTRAAL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "humanAL.h"

typedef struct dijkstraNode {
    int id;
    int dist;
} dijkstraNode;

typedef struct dijkstraCell {
    dijkstraNode* h;
    struct dijkstraCell* next;
} dijkstraCell;

typedef struct dijkstraPQ {
    int size;
    dijkstraCell* head;
    dijkstraCell* tail;
} dijkstraPQ;

extern void dijkstraInsert(dijkstraPQ* q, dijkstraNode* h);
extern dijkstraNode* dijkstraExtractMin(dijkstraPQ* q);
extern dijkstraNode* createNode(int id, int dist);
extern bool dijkstraIsEmpty(dijkstraPQ* q);
extern void dijkstra_spread(AL* G, int source, cost* c);

#endif