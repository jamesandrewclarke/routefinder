//
// Created by James Clarke on 17/04/2021.
//

#include "dataset.h"
#include "graph.h"
#include "dijkstra.h"

#include <stdio.h>

int main()
{
    FILE *fp = fopen("../../data/Final_Map.map", "r");
    Dataset *result = ingest(fp);

    Graph *graph = createGraph(result->numNodes);

    for (int i = 0; i < result->numLinks; i++)
    {
        Link *link = result->links + i;
        unsigned int start = 0;
        unsigned int end = 0;
        for (int j = 0; j < result->numNodes; j++)
        {
            MapNode *node = result->nodes + j;
            if (node->id == link->start) {
                start = node->internal_id;
            } else if (node->id == link->end)
            {
                end = node->internal_id;
            }
        }

        if (start == 0 && end == 0)
        {
            fprintf(stderr, "Error creating edges on the graph.\n");
        } else {
            createEdge(graph, start, end, link->length, 1);
        }
    }

    const unsigned int start = 0;
    const unsigned int end = 900;

    Route *route = dijkstra_shortestRoute(graph, start, end);
    if (route != NULL)
    {
        printf("Total Nodes: %i\n", route->numVertices);
        printf("Length: %f\n", route->cost);
    } else
    {
        fprintf(stderr, "A route could not be found between these nodes.\n");
    }

    printf("Route: ");
    for (int i = 0; i < route->numVertices; i++)
    {
        printf("%i, ", route->nodes[i]);
    }
}