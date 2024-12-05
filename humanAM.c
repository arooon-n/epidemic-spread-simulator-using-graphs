#include "humanAM.h"

human* createHuman(int Immunity) {
    human *h = (human*)malloc(sizeof(human));
    h->idx = -1;  // idx will be assigned later
    h->infected = 0;
    h->Immunity = Immunity;
    return h;
}

void infect(human* h) {
    h->infected = 1;
}

int allInfected(AM *a) {
    for (int i = 0; i < a->size; i++) {
        if (a->humans[i]->infected == 0) {
            return 0;
        }
    }
    return 1;
}

void printHuman(human *h) {
    printf("Human %d: ", h->idx);
    if (h->infected) {
        printf("Infected\n");
    } else {
        printf("Not Infected\n");
    }
    printf("Immunity: %d\n", h->Immunity);
}

AM* createAM(int n) {
    AM *a = (AM*)malloc(sizeof(AM));
    a->size = n;
    a->humans = (human**)malloc(n * sizeof(human*));
    a->matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        a->humans[i] = NULL;
        a->matrix[i] = (int*)calloc(n, sizeof(int));
    }
    return a;
}

void addHuman(AM *a, int idx, int Immunity) {
    human *h = createHuman(Immunity);
    h->idx = idx;
    a->humans[idx] = h;
}

void addEdge(AM *a, int h1, int h2, int weight) {
    a->matrix[h1][h2] = weight;
    a->matrix[h2][h1] = weight;
}

void printAM(AM *a) {
    printf("Adjacency Matrix:\n");
    printf("   ");
    for (int i = 0; i < a->size; i++) {
        printf("%3d", i);
    }
    printf("\n");
    for (int i = 0; i < a->size; i++) {
        printf("%3d", i);
        for (int j = 0; j < a->size; j++) {
            printf("%3d", a->matrix[i][j]);
        }
        printf("\n");
    }
}
