//
// Created by James Clarke on 14/04/2021.
//

#include "unity.h"
#include "dataset.h"
#include "dijkstra.h"
#include "convert.h"
#include <stdio.h>

static Dataset *dataset;
static Graph *graph;
static Route *route;

void setUp()
{
    FILE *fp = fopen("../../data/Final_Map.map", "r");
    TEST_ASSERT_NOT_NULL_MESSAGE(fp, "Test file could not be opened.\n");

    dataset = ingest(fp);
    fclose(fp);
    graph = datasetToGraph(dataset);
}

void tearDown()
{
    deleteDataset(dataset);
    deleteGraph(graph);
    deleteRoute(route);
}

// The following cases are (simple) solutions produced by the program that we know to be correct
// We check against these for regression testing

void integration_test(void)
{
    route = dijkstra_shortestRoute(graph, 7, 10);

    TEST_ASSERT_EQUAL_INT(4, route->numVertices);
    TEST_ASSERT_EQUAL_FLOAT(29.596424, route->cost);
    TEST_ASSERT_EQUAL_INT_ARRAY(((unsigned int[]){7,8,11,10}), route->nodes, 4);
    TEST_ASSERT_NOT_NULL(route);
}


void integration_test2(void)
{
    route = dijkstra_shortestRoute(graph, 1000, 1005);

    TEST_ASSERT_EQUAL_INT(6, route->numVertices);
    TEST_ASSERT_EQUAL_FLOAT(41.317493, route->cost);
    TEST_ASSERT_EQUAL_INT_ARRAY(((unsigned int[]){1000, 1001, 1002, 1003, 1004, 1005}), route->nodes, 6);
    TEST_ASSERT_NOT_NULL(route);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(integration_test);
    RUN_TEST(integration_test2);

    return UNITY_END();
}

