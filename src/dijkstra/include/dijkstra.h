#pragma once

#include "graph.h"

typedef struct Route Route;

struct Route {
    int numVertices;
    float cost;
    unsigned int* nodes;
};

Route *dijkstra_shortestRoute(const Graph *graph, unsigned int start, unsigned int end);

int deleteRoute(Route *route);