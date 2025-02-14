//
// Created by James Clarke on 12/03/2021.
//

#include "include/graph.h"
#include <stdlib.h>

Graph *createGraph(const unsigned int vertices)
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
        Edge *head = adjList->head;
        // Free the linked list
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

Edge *createEdge(Graph *graph, const unsigned int start, const unsigned int end, const float weight, const int undirected)
{
    if (graph == NULL) return NULL;
    if (start > graph->numVertices || end > graph->numVertices || start == end) return NULL;

    Edge **head_ref = &graph->vertices[start].head;

    // Select the pointer for 'head_ref' to insert edges in ascending order of weight
    if (*head_ref != NULL)
    {
        while ((*head_ref)->weight < weight)
        {
            head_ref = &(*head_ref)->next;
            if (*head_ref == NULL)
            {
                break;
            }
        }

        if (*head_ref != NULL)
        {
            // Check that the edge doesn't already exist...
            if ((*head_ref)->weight == weight && (*head_ref)->vertex == end) return NULL;
        }
    }

    // Allocate a new edge
    Edge *new = calloc(1, sizeof(Edge));
    new->vertex = end;
    new->weight = weight;
    new->next = *head_ref;
    *head_ref = new;

    if (undirected)
    {
        createEdge(graph, end, start, weight, 0);
    }

    return new;
}
