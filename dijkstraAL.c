#include "dijkstraAL.h"
#include "humanAL.h"
#include <limits.h>

int minDistance(int dist[], bool sptSet[], int size) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < size; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra_spread(AL* graph, int src, cost* c) {
    infect(graph->p[src].human);
    int size = graph->size;
    int dist[size];
    bool sptSet[size];
    int parent[size];

    for (int i = 0; i < size; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < size - 1; count++) {
        int u = minDistance(dist, sptSet, size);
        sptSet[u] = true;

        edgeList* temp = graph->p[u].head;
        while (temp != NULL) {
            int v = temp->edge->human2->idx;
            int weight = temp->edge->weight + temp->edge->human2->Immunity;
            if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
            }
            temp = temp->next;
        }
    }

    for (int i = 0; i < size; i++) {
        if (i != src && parent[i] != -1) {
            infect(graph->p[i].human);
            c->days++;
            c->cost += dist[i];
            printf("Infected human %d with cost %d on day %d\n", i, c->cost, c->days);
        }
    }
}