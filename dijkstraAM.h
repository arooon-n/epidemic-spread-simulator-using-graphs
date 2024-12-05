#ifndef DIJKSTRAAM_H
#define DIJKSTRAAM_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "humanAM.h"


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

dijkstraPQ* createQueue();
dijkstraNode* createNode(int id, int dist);
void dijkstraInsert(dijkstraPQ* q, dijkstraNode* h);
dijkstraNode* dijkstraExtractMin(dijkstraPQ* q);
bool dijkstraIsEmpty(dijkstraPQ* q);
void dijkstra_spreadAM(AM* graph, int src, cost* c);

#endif