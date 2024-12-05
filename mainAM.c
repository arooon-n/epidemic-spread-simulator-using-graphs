#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "humanAM.h"
#include "greedyAM.h"
#include "primsAM.h"
#include "greedy_immunityAM.h"
#include "dijkstraAM.h"

int main() {
    int n;
    scanf("%d", &n);
        if(n == 0) {
        printf("There must be atleast one Human.\n");
        return 0;
    }
    int m;
    scanf("%d", &m);
    AM *a = createAM(n);
    for (int i = 0; i < n; i++) {
        int Immunity;
        scanf("%d", &Immunity);
        addHuman(a, i, Immunity);
    }
    for (int i = 0; i < m; i++) {
        int weight, h1, h2;
        scanf("%d %d %d", &weight, &h1, &h2);
        addEdge(a, h1, h2, weight);
    }
    printf("\n");
   // printAM(a);
    printf("\n");
    cost *c = malloc(sizeof(cost));
    int type;
    scanf("%d", &type);
    if(type == 1) {
        greedy_spread(a, 0, c);
    } else if(type == 2) {
        prims_spread(a, 0, c);

    } else if(type == 3) {
        greedy_Im_spread(a, 0, c);
    }
    else if(type == 4) {
        dijkstra_spreadAM(a, 0, c);
    }
    else {
        printf("Invalid choice\n");
    }
    if(allInfected(a)) {
        printf("\nAll humans are infected\n");
    } else {
        printf("\nAll humans cannot be infected\n");
    }
    return 0;
}
