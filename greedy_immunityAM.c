#include "greedy_immunityAM.h"

void greedy_Im_spread(AM *a, int source, cost* c) {
    if (allInfected(a)) {
        c->cost = 0;
        c->days = 0;
        return;
    }
    
    if (!a->humans[source]->infected) {
        infect(a->humans[source]);
        printf("Infected human %d with cost %d on day %d\n", source, c->cost, c->days);
    }
    int min_cost = INT_MAX;
    int min_idx = -1;
    for (int i = 0; i < a->size; i++) {
        if (a->matrix[source][i] != 0 && !a->humans[i]->infected) {
            int current_cost = a->humans[i]->Immunity;
            if (current_cost < min_cost) {
                min_cost = current_cost;
                min_idx = i;
            }
        }
    }
    if (min_idx == -1) {
        return;
    }
    c->days++;
    c->cost += min_cost;
    greedy_Im_spread(a, min_idx, c);
    greedy_Im_spread(a, source, c);
}
