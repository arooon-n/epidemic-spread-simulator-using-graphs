#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "humanAL.h"
#include "greedyAL.h"
#include "primsAL.h"
#include "greedy_immunityAL.h"
#include "dijkstraAL.h"

int main() {
    int n;
    //printf("Enter the number of humans: ");
    scanf("%d", &n);
    if(n == 0) {
        printf("There must be atleast one Human.\n");
        return 0;
    }
    int m;
    //printf("Enter the number of edges: ");
    scanf("%d", &m);

    AL *a = createAL(n);
    for (int i = 0; i < n; i++) {
        int Immunity;
        //printf("Enter the immunity of human %d: ", i);
        scanf("%d", &Immunity);
        a = addHumans(a, Immunity);
    }

    for (int i = 0; i < m; i++) {
        int weight;
        int h1;
        int h2;
        //printf("Enter the weight of edge %d and its src and dest: ", i+1);
        scanf("%d %d %d", &weight, &h1, &h2);
        a = addEdge(a, h1, h2, weight);
    }
    printf("\n");

    //printAL(a);
    printf("\n");

    cost *c = malloc(sizeof(cost));

    int type;
    //printf("Enter 1 for greedy and 2 for prims and 3 for greedy based on immunity: ");
    scanf("%d", &type);

    if(type == 1) {
        int source;
        // //printf("Enter the source vertex: ");
        // scanf("%d", &source);
        greedy_spread(a, 0, c);
    } else if(type == 2) {
        int source;
        // //printf("Enter the source vertex: ");
        // scanf("%d", &source);
        prims_spread(a, 0, c);
    } else if(type == 3) {
        int source;
        // //printf("Enter the source vertex: ");
        // scanf("%d", &source);
        greedy_Im_spread(a, 0, c);
    }
    else if(type == 4) {
        int source;
        // //printf("Enter the source vertex: ");
        // scanf("%d", &source);
        dijkstra_spread(a, 0, c);
    }

    if(allInfected(a)) {
        printf("\nAll humans are infected\n");
    } else {
        printf("\nAll humans cannot be infected\n");
    }
    return 0;
}