//
// Created by James Clarke on 10/03/2021.
//

#include <stdlib.h>
#include "include/graph.h"

Graph *createGraph()
{
    Graph *graph = malloc(sizeof(Graph));
    graph->nodeHead = NULL;
    graph->edgeHead = NULL;
    return graph;
}

int deleteGraph(Graph *graph)
{
    Node *node = graph->nodeHead;
    // Traverse the linked list and free each node pointer
    while (node != NULL)
    {
        Node *next = node->next;
        free(node);
        node = next;
    }
    free(graph);

    return 1;
}

Node *addNode(Graph *graph, unsigned int id)
{
    if (graph == NULL) return NULL;

    Node *new = malloc(sizeof(Node));
    new->id = id;

    new->next = graph->nodeHead;
    new->previous = NULL;
    graph->nodeHead = new;

    return new;
}

Node *findNode(Graph *graph, unsigned int id)
{
    // stub
    return NULL;
}

int deleteNode(Graph *graph, Node *node)
{
    // stub
    return 0;
}

Edge *addEdge(Graph *graph, Node *start, Node *End, double weight)
{
    // stub
    return NULL;
}

int deleteEdge(Graph *graph, Edge *edge)
{
    // stub
    return 0;
}

