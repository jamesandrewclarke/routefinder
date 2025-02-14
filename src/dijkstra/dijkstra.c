//
// Created by James Clarke on 29/03/2021.
//

#include "include/dijkstra.h"
#include "include/queue.h"
#include <stdlib.h>
#include <float.h>

Route *getRoute(const DijkstraResult *result, const unsigned int end)
{
    if (result->prev[end] == UNDEFINED)
    {
        return NULL; // the end vertex is not reachable
    }

    Route *route = malloc(sizeof(Route));
    route->cost = result->dist[end];

    unsigned int next = result->prev[end];
    int vertices = 1;
    while (next != UNDEFINED)
    {
        next = result->prev[next];
        vertices++;
    }

    unsigned int *nodes = calloc(vertices, sizeof(unsigned int *));
    next = end;
    for (int i = 0; i < vertices; i++)
    {
        nodes[vertices - 1 - i] = next;
        next = result->prev[next];
    }
    route->numVertices = vertices;
    route->nodes = nodes;

    return route;
}

DijkstraResult *dijkstra(const Graph *graph, const unsigned int start)
{
    // Pseudocode from https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Using_a_priority_queue
    float *dist = calloc(graph->numVertices, sizeof(float));
    unsigned int *prev = calloc(graph->numVertices, sizeof(unsigned int));
    dist[start] = 0;
    prev[start] = UNDEFINED;

    PriorityQueue *Q = createQueue();

    for (int i = 0; i < graph->numVertices; i++)
    {
        if (i != start)
        {
            dist[i] = INF;
            prev[i] = UNDEFINED;
        }

        addWithPriority(Q, i, dist[i]);
    }

    while (!queueIsEmpty(Q))
    {
        const Node minNode = extractMin(Q);
        const unsigned int u = minNode.id;

        Edge *ref = (graph->vertices + u)->head;
        // Traverse the linked list to find the closest node
        while (ref != NULL)
        {
            unsigned int v = ref->vertex;
            float alt = dist[u] + ref->weight;

            if (alt < dist[v])
            {
                dist[v] = alt;
                prev[v] = u;
                changePriority(Q, v, alt);
            }
            ref = ref->next;
        }

    }

    deleteQueue(Q);

    DijkstraResult *result = malloc(sizeof(DijkstraResult));
    result->prev = prev;
    result->dist = dist;

    return result;
}

Route *dijkstra_shortestRoute(const Graph *graph, const unsigned int start, const unsigned int end)
{
    if (end > graph->numVertices) return NULL;

    DijkstraResult *result = dijkstra(graph, start);

    // The algorithm is complete, now we have to record the route
    Route *route = getRoute(result, end);

    deleteResult(result);
    return route;
}

int deleteRoute(Route *route)
{
    if (route == NULL) return 0;
    free(route->nodes);
    free(route);
    return 1;
}

int deleteResult(DijkstraResult *result)
{
    if (result == NULL) return 0;
    free(result->prev);
    free(result->dist);
    free(result);
    return 1;
}