//
// Created by James Clarke on 12/03/2021.
//

#include "include/graph.h"
#include <stdlib.h>

Graph *createGraph(unsigned int vertices)
{
    if (vertices == 0) return NULL;

    Graph *new = malloc(sizeof(Graph));
    new->numVertices = vertices;
    new->vertices = calloc(vertices, sizeof(AdjacencyList));

    for (int i = 0; i < new->numVertices; i++)
    {
        AdjacencyList *adjList = new->vertices + i;
        adjList->vertex = i;
        adjList->head = NULL;
    }

    return new;
}

int deleteGraph(Graph *graph)
{
    if (graph == NULL) return 0;

    for (int i = 0; i < graph->numVertices; i++)
    {
        AdjacencyList *adjList = graph->vertices + i;

        // First we need to clear out the linked lists

        Edge *head = adjList->head;

        while (head != NULL)
        {
            Edge *next = head->next;
            free(head);
            head = next;
        }
    }

    free(graph->vertices);
    free(graph);

    return 1;
}

Edge *createEdge(Graph *graph, unsigned int start, unsigned int end, float weight, int directional)
{
    if (graph == NULL) return NULL;
    if (start > graph->numVertices || end > graph->numVertices || start == end) return NULL;

    Edge **head_ref = &graph->vertices[start].head;

    if (*head_ref != NULL)
    {
        while ((*head_ref)->weight < weight)
        {
            head_ref = &(*head_ref)->next;
            if (*head_ref == NULL) break;
        }
    }
    // Allocate a new edge
    Edge *new = calloc(1, sizeof(Edge));
    new->vertex = end;
    new->weight = weight;
    new->next = *head_ref;
    *head_ref = new;

    if (directional)
    {
        createEdge(graph, end, start, weight, 0);
    }

    return new;
}



