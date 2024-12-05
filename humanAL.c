#include "humanAL.h"

human* createHuman( int Immunity) {
    human *h = (human*)malloc(sizeof(human));
    h->idx = -1;
    h->infected = 0;
    h->Immunity = Immunity;
    return h;
}

void infect(human* h) {
    h->infected = 1;
}

int allInfected(AL *a) {
    for (int i = 0; i < a->size; i++) {
        if (a->p[i].human->infected == 0) {
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

edge* createEdge(AL*a,int weight, int h1, int h2) {
    edge *e = (edge*)malloc(sizeof(edge));
    e->weight = weight;
    e->human1 = a->p[h1].human;
    e->human1->idx = h1;
    e->human2 = a->p[h2].human; 
    e->human2->idx = h2;
    return e;
}

void printEdge(edge *e) {
    printf("%d", e->human2->idx);
}

AL* createAL(int n) {
    AL *a = (AL*)malloc(sizeof(AL));
    a->size = n;
    a->p = (humanList*)malloc(n * sizeof(humanList));
    for (int i = 0; i < n; i++) {
        a->p[i].human = NULL;
        a->p[i].head = NULL;
        a->p[i].tail = NULL;
    }
    return a;
}

AL* addHumans(AL *a, int Immunity) {
    human *h = createHuman(Immunity);
    for (int i = 0; i < a->size; i++) {
        if (a->p[i].human == NULL) {
            a->p[i].human = h;
            a->p[i].human->idx = i;
            break;
        }
    }
    return a;
}

edgeList* createEdgeList(edge *e) {
    edgeList *el = (edgeList*)malloc(sizeof(edgeList));
    el->edge = e;
    el->next = NULL;
    return el;
}

humanList* createHumanList() {
    humanList *hl = (humanList*)malloc(sizeof(humanList));
    hl->human = NULL;
    hl->head = NULL;
    hl->tail = NULL;
    return hl;
}

AL* addEdge(AL *a, int h1, int h2, int weight) {
    edge *e = createEdge(a, weight, h1, h2);
    edgeList *el = createEdgeList(e);
    if (a->p[h1].head == NULL) {
        a->p[h1].head = el;
        a->p[h1].tail = el;
    } else {
        a->p[h1].tail->next = el;
        a->p[h1].tail = el;
    }

    e = createEdge(a,weight, h2, h1);
    el = createEdgeList(e);
    if (a->p[h2].head == NULL) {
        a->p[h2].head = el;
        a->p[h2].tail = el;
    } else {
        a->p[h2].tail->next = el;
        a->p[h2].tail = el;
    }
    return a;
}

void printEdgeList(edgeList *el) {
    edgeList* temp = el;
    while (temp != NULL) {
        printf(" ->");
        printEdge(temp->edge);
        printf("(%d)",temp->edge->weight);
        temp = temp->next;
    }
    printf("\n");
}

void printAL(AL *a) {
    for (int i = 0; i < a->size; i++) {
        printf("%d:", a->p[i].human->idx);
        printEdgeList(a->p[i].head);
    }
}