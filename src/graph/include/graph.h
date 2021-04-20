//
// Created by James Clarke on 12/03/2021.
//

#pragma once

typedef struct AdjacencyList AdjacencyList;
typedef struct Edge Edge;
typedef struct Graph Graph;

struct Graph
{
    unsigned int numVertices;
    AdjacencyList *vertices;
};

struct AdjacencyList
{
    unsigned int vertex;
    Edge *head;
};

struct Edge
{
    unsigned int vertex;
    float weight;
    Edge *next;
};

/**
 * Allocates and initialises fields of a graph
 * @param vertices The number of vertices, must be greater than zero.
 * @return A pointer to the new graph
 */
Graph *createGraph(unsigned int vertices);

/**
 * Frees the memory used by a Graph
 * @param graph The graph to delete
 * @return A status code, 1 if successful
 */
int deleteGraph(Graph *graph);

/**
 * Creates a weighted edge between two vertices
 * @param graph The graph to create an edge in
 * @param start The index of the starting vertex
 * @param end The index of the destination vertex
 * @param weight The weight of the edge
 * @param undirected Should not be 0 if a directed edge
 * @return A pointer to the new edge
 */
Edge *createEdge(Graph *graph, const unsigned int start, const unsigned int end, const float weight, const int undirected);
