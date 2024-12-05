#include "greedy_immunityAL.h"

edge* getMin_Im(humanList* l) {
    if (l == NULL || l->head == NULL) {
        return NULL;
    }
    edgeList* temp = l->head;
    edgeList* min = NULL;
    int min_cost = INT_MAX;
    while (temp != NULL) {
        if (temp->edge->human2->infected == 0) {
            int current_cost =temp->edge->human2->Immunity;
            if(min != NULL)min_cost =  min->edge->human2->Immunity;
            if (current_cost < min_cost) {
                min = temp;
            }
        }
        temp = temp->next;
    }
    if(min == NULL) return NULL;
    return min->edge;
}

void greedy_Im_spread(AL *a, int source, cost* c) {
    if (allInfected(a)) {
    c->cost = 0;
    c->days = 0;
        return;
    }
    
    if (!a->p[source].human->infected) {
        infect(a->p[source].human);
        printf("Infected human %d with cost %d on day %d\n", source, c->cost, c->days);
    }

    edge* min_edge = getMin_Im(a->p+source);
    
    if (min_edge == NULL) {
        return;
    }
    if (min_edge != NULL) {
        c->days++;
        c->cost += min_edge->weight + min_edge->human2->Immunity;
        greedy_Im_spread(a, min_edge->human2->idx,c);
    }
    greedy_Im_spread(a, source, c);
}