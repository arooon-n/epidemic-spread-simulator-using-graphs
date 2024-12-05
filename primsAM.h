#ifndef PRIMS_AM_H
#define PRIMS_AM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "humanAM.h"

typedef struct node {
    int id;
    int weight;
    int Immunity;
} node;

typedef struct cell {
    node* h;
    struct cell* next;
} cell;

typedef struct priorityQueue {
    int size;
    cell* head;
    cell* tail;
} pq;

void insert(pq* q, node* h);
bool isEmpty(pq* q);
node* extractMin(pq* q);
void prims_spread(AM* G, int source, cost* c);

#endif
