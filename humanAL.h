#ifndef HUMAN_H
#define HUMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct edgeList edgeList;

typedef struct human {
    int idx;
    int infected;
    int Immunity;
} human;

typedef struct edge {
    int weight;
    human *human1;
    human *human2;
} edge;

typedef struct humanList {
    human* human;
    edgeList* head;
    edgeList* tail;
} humanList;

struct edgeList {
    edge* edge;
    struct edgeList* next;
};

typedef struct AL {
    int size;
    humanList* p;
} AL;

typedef struct cost {
    int cost;
    int days;
} cost;

extern void infect(human*);
extern human* createHuman(int);  
extern void printHuman(human*);
extern edge* createEdge(AL*, int, int, int);
extern void printEdge(edge*);
extern AL* createAL(int);
extern AL* addHumans(AL*, int);
extern AL* addEdge(AL*, int, int, int);
extern edgeList* createEdgeList(edge*);
extern humanList* createHumanList();
extern void printAL(AL*);
extern void printEdgeList(edgeList*);
int allInfected(AL*);

#endif