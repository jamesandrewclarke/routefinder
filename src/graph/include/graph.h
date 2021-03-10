//
// Created by James Clarke on 10/03/2021.
//

#ifndef ROUTEFINDER_GRAPH_H
#define ROUTEFINDER_GRAPH_H

typedef struct Node Node;
typedef struct Edge Edge;

struct Node
{
    unsigned int id;
    Node *previous;
    Node *next;
};

struct Edge
{
    Node *start;
    Node *end;
    double weight;
    Edge *previous;
    Edge *next;
};

/**
 * Represents a simple weighted graph
 * Contains a set of nodes and the edges connecting them.
 * @remarks Both sets are doubly linked lists
 */
typedef struct
{
    Node *nodeHead;
    Edge *edgeHead;
} Graph;


/**
 * Allocates and initialises fields for a Graph struct
 * @return A pointer to a Graph
 */
Graph *createGraph();

/**
 * Deletes all nodes and frees a graph from memory
 * @param graph The graph to delete
 * @returns 1 if successful
 */
int deleteGraph(Graph *graph);

/**
 * Adds a node to a Graph
 * @param graph The graph to add the node to
 * @param id A unique identifier for the node
 * @return A pointer to the new node
 */
Node *addNode(Graph *graph, unsigned int id);

/**
 * Searches for a node by its id
 * @param graph The graph to search
 * @param id The id to use as a search parameter
 * @return If one exists, the pointer to the node, or NULL.
 */
Node *findNode(Graph *graph, unsigned int id);

/**
 * Removes a node from a graph and deletes from memory
 * @param graph The graph to remove the node from
 * @param node The node to remove
 * @return 1 if successful
 */
int deleteNode(Graph *graph, Node *node);

/**
 * Adds a weighted edge connecting two nodes in the graph
 * @param graph The graph to add the node to
 * @param start The starting node
 * @param end The ending node
 * @param weight The edges weight, can not be negative
 * @return A pointer to the new edge
 */
Edge *addEdge(Graph *graph, Node *start, Node *end, double weight);

/**
 * Removes an edge from the graph
 * @param graph The graph to remove the edge from
 * @param edge The edge to remove
 * @return 1 if successful
 */
int deleteEdge(Graph *graph, Edge *edge);

#endif //ROUTEFINDER_GRAPH_H
