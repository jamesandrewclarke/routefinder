#pragma once

#include "graph.h"

typedef struct Route Route;
typedef struct DijkstraResult DijkstraResult;

struct Route
{
    int numVertices;
    float cost;
    unsigned int *nodes;
};

struct DijkstraResult
{
    float *dist;
    unsigned int *prev;
};

/**
* Produces an array of a path to the 'end' node from a given DijkstraResult
* @param result The DijkstraResult to find the path from.
* @param end The ID of the 'end' node.
* @return A Route struct.
*/
Route *getRoute(const DijkstraResult *result, unsigned int end);

/**
* Finds the shortest path between the 'start' node and every other node in the graph.
* @param graph The graph containing all other nodes
* @param start The ID of the start node.
* @return A DijkstraResult struct containing both a distance and precedence array.
*/
DijkstraResult *dijkstra(const Graph *graph, unsigned int start);

Route *dijkstra_shortestRoute(const Graph *graph, unsigned int start, unsigned int end);

int deleteRoute(Route *route);

int deleteResult(DijkstraResult *result);