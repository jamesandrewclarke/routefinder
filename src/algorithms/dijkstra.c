//
// Created by James Clarke on 29/03/2021.
//

#include "include/dijkstra.h"
#include "include/queue.h"
#include "stdlib.h"
#include "float.h"

Route *dijkstra_shortestRoute(Graph *graph, unsigned int start, unsigned int end)
{
    // Pseudocode from https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Using_a_priority_queue
    float *dist = calloc(graph->numVertices, sizeof(float));
    unsigned int *prev = calloc(graph->numVertices, sizeof(unsigned int));
    dist[start] = 0;
    prev[start] = UNDEFINED;

    PriorityQueue *Q = createQueue();

    for (int i = 0; i < graph->numVertices; i++)
    {
        if (i != start) {
            dist[i] = INF;
            prev[i] = UNDEFINED;
        }

        addWithPriority(Q, i, dist[i]);
    }

    while(!queueIsEmpty(Q))
    {
        Node minNode = extractMin(Q);
        unsigned int u = minNode.id;

        Edge *ref = (graph->vertices + u)->head;
        while (ref != NULL)
        {
            unsigned int v = ref->vertex;
            float alt = dist[u] + ref->weight;

            if (alt < dist[v]) {
                dist[v] = alt;
                prev[v] = u;
                changePriority(Q, v, alt);
            }
            ref = ref->next;
        }

    }

    // backtrack through

    if (prev[end] == UNDEFINED) {
        free(dist);
        free(prev);
        deleteQueue(Q);
        return NULL; // the end vertex is not reachable
    }

    Route *route = malloc(sizeof(Route));
    route->cost = dist[end];

    unsigned int next = prev[end];
    int vertices = 1;
    while (next != UNDEFINED)
    {
        next = prev[next];
        vertices++;
    }

    unsigned int *nodes = calloc(vertices, sizeof(unsigned int*));
    next = end;
    for (int i = 0; i < vertices; i++)
    {
        nodes[vertices - 1 - i] = next;
        next = prev[next];
    }
    route->numVertices = vertices;
    route->nodes = nodes;

    free(dist);
    free(prev);

    deleteQueue(Q);
    return route;
}

int deleteRoute(Route *route)
{
    if (route == NULL) return 0;
    free(route->nodes);
    free(route);
    return 1;
}