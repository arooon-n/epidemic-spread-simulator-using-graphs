#include "primsAM.h"

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
                    free(temp->h);
                    free(temp);
                    q->size--;
                    break;
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

void freeQueue(pq* q) {
    while (!isEmpty(q)) {
        node* node = extractMin(q);
        free(node);
    }
    free(q);
}

void prims_spread(AM* G, int source, cost* c) {
    pq* queue = malloc(sizeof(pq));
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;

    bool* visited = calloc(G->size, sizeof(bool));
    visited[source] = true;
    infect(G->humans[source]);

    for (int i = 0; i < G->size; i++) {
        if (G->matrix[source][i] != 0 && !visited[i]) {
            node* n = malloc(sizeof(node));
            n->id = i;
            n->weight = G->matrix[source][i];
            n->Immunity = G->humans[i]->Immunity;
            insert(queue, n);
        }
    }

    while (!isEmpty(queue)) {
        node* min = extractMin(queue);
        if (!visited[min->id]) {
            visited[min->id] = true;
            infect(G->humans[min->id]);
            c->days++;
            c->cost += min->weight + min->Immunity;
            printf("Infected human %d with cost %d on day %d\n", min->id, c->cost, c->days);
            for (int i = 0; i < G->size; i++) {
                if (G->matrix[min->id][i] != 0 && !visited[i]) {
                    node* n = malloc(sizeof(node));
                    n->id = i;
                    n->weight = G->matrix[min->id][i];
                    n->Immunity = G->humans[i]->Immunity;
                    insert(queue, n);
                }
            }
        }
        free(min);
    }

    freeQueue(queue);
    free(visited);
}