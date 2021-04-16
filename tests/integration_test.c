//
// Created by James Clarke on 14/04/2021.
//

#include "graph.h"
#include "unity.h"
#include "dataset.h"
#include "dijkstra.h"
#include <stdio.h>

void setUp()
{
}

void tearDown()
{
}

void integration_test(void)
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
            fprintf(stderr, "RUN!!\n");
        } else {
            createEdge(graph, start, end, link->length, 1);
        }
    }

    Route *route = dijkstra_shortestRoute(graph, 7, 500);
    if (route != NULL)
    {
        printf("Total Nodes: %i\n", route->numVertices);
        printf("Length: %f\n", route->cost);
    } else
    {
        fprintf(stderr, "No route found.\n");
    }

    printf("Route: ");
    for (int i = 0; i < route->numVertices; i++)
    {
        printf("%i, ", route->nodes[i]);
    }

    printf("\n");

    deleteDataset(result);
    fclose(fp);

    deleteRoute(route);
    deleteGraph(graph);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(integration_test);

    return UNITY_END();
}

