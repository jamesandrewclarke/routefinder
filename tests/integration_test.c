//
// Created by James Clarke on 14/04/2021.
//

#include "unity.h"
#include "dataset.h"
#include "dijkstra.h"
#include "convert.h"
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

    Graph *graph = datasetToGraph(result);

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

