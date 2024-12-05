#ifndef HUMAN_AM_H
#define HUMAN_AM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct human {
    int idx;
    int infected;
    int Immunity;
} human;

typedef struct AM {
    int size;
    human** humans;
    int** matrix;
} AM;

typedef struct cost {
    int cost;
    int days;
} cost;

human* createHuman(int Immunity);
void infect(human* h);
int allInfected(AM *a);
void printHuman(human *h);
AM* createAM(int n);
void addHuman(AM *a, int idx, int Immunity);
void addEdge(AM *a, int h1, int h2, int weight);
void printAM(AM *a);

#endif
