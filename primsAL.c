#include "primsAL.h"
#include "humanAL.h"

bool isEmpty(pq* q) {
    return q->size == 0;
}

void insert(pq* q, node* h) {
    cell* c = malloc(sizeof(cell));
    c->h = h;
    c->next = NULL;
    
    if (isEmpty(q)) {
        q->head = c;
        q->tail = c;
    } else {
        cell* temp = q->head;
        cell* prev = NULL;
        int new_cost = h->weight + h->Immunity;
        
        while (temp != NULL) {
            if (temp->h->id == h->id) {
                if (new_cost < temp->h->weight + temp->h->Immunity) {
                    if (prev != NULL) prev->next = temp->next;
                    else q->head = temp->next;
                    free(temp);
                    q->size--;
                    break;
                } else {
                    free(c);
                    return;
                }
            }
            prev = temp;
            temp = temp->next;
        }
        
        temp = q->head;
        prev = NULL;
        
        while (temp != NULL && (temp->h->weight + temp->h->Immunity) <= new_cost) {
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

node* extractMin(pq* q) {
    if (isEmpty(q)) return NULL;
    
    cell* temp = q->head;
    q->head = q->head->next;
    if (q->head == NULL) q->tail = NULL;
    
    node* min = temp->h;
    free(temp);
    q->size--;
    return min;
}

void prims_spread(AL* G, int source, cost* c) {
    pq* queue = malloc(sizeof(pq));
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;
    
    bool* visited = calloc(G->size, sizeof(bool));
    c->cost = 0;
    c->days = 0;

    visited[source] = true;
    infect(G->p[source].human);
    printf("Infected human %d with cost %d on day %d\n", source, c->cost, c->days);

    edgeList* edge = G->p[source].head;
    while (edge != NULL) {
        if (!edge->edge->human2->infected) {
            node* n = malloc(sizeof(node));
            n->id = edge->edge->human2->idx;
            n->weight = edge->edge->weight;
            n->Immunity = edge->edge->human2->Immunity;
            insert(queue, n);
        }
        edge = edge->next;
    }

    while (!isEmpty(queue) && !allInfected(G)) {
        node* min = extractMin(queue);
        if (!visited[min->id]) {
            visited[min->id] = true;
            infect(G->p[min->id].human);
            c->days++;
            c->cost += min->weight + min->Immunity;
            
            printf("Infected human %d with cost %d on day %d\n", 
                   min->id, c->cost, c->days);

            edge = G->p[min->id].head;
            while (edge != NULL) {
                if (!visited[edge->edge->human2->idx]) {
                    node* n = malloc(sizeof(node));
                    n->id = edge->edge->human2->idx;
                    n->weight = edge->edge->weight;
                    n->Immunity = edge->edge->human2->Immunity;
                    insert(queue, n);
                }
                edge = edge->next;
            }
        }
        free(min);
    }

    free(queue);
    free(visited);
}
