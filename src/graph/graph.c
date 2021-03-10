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
    if (graph == NULL) return 0;
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

    // Guard against duplicate IDs
    if (findNode(graph, id) != NULL) return NULL;

    Node *new = malloc(sizeof(Node));
    new->id = id;

    new->next = graph->nodeHead;
    new->previous = NULL;
    graph->nodeHead = new;

    return new;
}

Node *findNode(Graph *graph, unsigned int id)
{
    if (graph == NULL) return NULL;

    Node *node = graph->nodeHead;
    // Traverse the linked list
    while (node != NULL)
    {
        if (node->id == id)
        {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

int deleteNode(Graph *graph, Node *node)
{
    if (node == NULL) return 0;
    Node *result = findNode(graph, node->id);
    if (result == NULL) return 0;

    // Fill the hole in the list by linking the previous node with the next
    if (node->previous != NULL)
    {
        node->previous->next = node->next;
    }

    // If removing the first node in the list
    if (graph->nodeHead == node)
    {
        graph->nodeHead = node->next;
    }

    free(node);

    return 1;
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

