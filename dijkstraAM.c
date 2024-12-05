#include "dijkstraAM.h"
#include "humanAM.h"
#include <limits.h>

bool dijkstraIsEmpty(dijkstraPQ* q) {
    return q->size == 0;
}

dijkstraPQ* createQueue() {
    dijkstraPQ* q = malloc(sizeof(dijkstraPQ));
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
    
    return q;
}

dijkstraNode* createNode(int id, int dist) {
    dijkstraNode* h = malloc(sizeof(dijkstraNode));
    h->id = id;
    h->dist = dist;
    return h;
}

void dijkstraInsert(dijkstraPQ* q, dijkstraNode* h) {
    dijkstraCell* c = malloc(sizeof(dijkstraCell));
    c->h = h;
    c->next = NULL;
    
    if (dijkstraIsEmpty(q)) {
        q->head = c;
        q->tail = c;
    } else {
        dijkstraCell* temp = q->head;
        dijkstraCell* prev = NULL;
        
        while (temp != NULL) {
            if (temp->h->id == h->id) {
                if (h->dist < temp->h->dist) {
                    temp->h->dist = h->dist;
                    free(c->h);
                    free(c);
                    return;
                } else {
                    free(c->h);
                    free(c);
                    return;
                }
            }
            prev = temp;
            temp = temp->next;
        }
        
        temp = q->head;
        prev = NULL;
        
        while (temp != NULL && temp->h->dist <= h->dist) {
            prev = temp;
            temp = temp->next;
        }
        
        if (prev == NULL) {
            c->next = q->head;
            q->head = c;
        } else {
            c->next = temp;
            prev->next = c;
        }
    }
    q->size++;
}

dijkstraNode* dijkstraExtractMin(dijkstraPQ* q) {
    if (dijkstraIsEmpty(q)) return NULL;
    
    dijkstraCell* temp = q->head;
    q->head = q->head->next;
    if (q->head == NULL) q->tail = NULL;
    
    dijkstraNode* min = temp->h;
    free(temp);
    q->size--;
    return min;
}

void dijkstra_spreadAM(AM* graph, int src, cost* c) {
    dijkstraPQ* queue = createQueue();
    
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
    dijkstraNode* start = createNode(src, 0);
    dijkstraInsert(queue, start);

    infect(graph->humans[src]);

    while (!dijkstraIsEmpty(queue)) {
        dijkstraNode* minNode = dijkstraExtractMin(queue);
        int u = minNode->id;
        free(minNode);

        if (sptSet[u]) continue;
        sptSet[u] = true;

        for (int v = 0; v < size; v++) {
            if (graph->matrix[u][v] != 0) {
                int weight = graph->matrix[u][v] + graph->humans[v]->Immunity;
                if (!sptSet[v] && dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    dijkstraNode* newNode = createNode(v, dist[v]);
                    dijkstraInsert(queue, newNode);
                }
            }
        }
    }

    for (int i = 0; i < size; i++) {
        if (i != src && parent[i] != -1) {
            infect(graph->humans[i]);
            c->days++;
            printf("Infected human %d with cost %d on day %d by %d\n", i, dist[i], c->days, parent[i]);
        }
    }

    free(queue);
}