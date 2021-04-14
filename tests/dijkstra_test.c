//
// Created by James Clarke on 29/03/2021.
//
#include "graph.h"
#include "dijkstra.h"
#include "unity.h"

void setUp()
{
}

void tearDown()
{
}

void dijkstra_CorrectParameters_ReturnsShortestRoute(void)
{
    Graph *graph = createGraph(6);

    // This problem is from https://www.programiz.com/dsa/dijkstra-algorithm
    createEdge(graph, 0, 1, 4, 1);
    createEdge(graph, 0, 2, 4, 1);
    createEdge(graph, 1, 2, 2, 1);
    createEdge(graph, 2, 3, 3, 1);
    createEdge(graph, 2, 4, 1, 1);
    createEdge(graph, 2, 5, 6, 1);
    createEdge(graph, 3, 5, 2, 1);
    createEdge(graph, 4, 5, 3, 1);

    Route *route = dijkstra_shortestRoute(graph, 0, 5);
    unsigned int expected[] = {0, 2, 4, 5};

    TEST_ASSERT_NOT_NULL(route);
    TEST_ASSERT_EQUAL_INT(4, route->numVertices);
    TEST_ASSERT_EQUAL_FLOAT(8, route->cost);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, route->nodes, 4);

    deleteGraph(graph);
    deleteRoute(route);
}

void dijkstra_CorrectParameters2_ReturnsShortestRoute(void)
{
    Graph *graph = createGraph(5);

    createEdge(graph, 0, 1, 3, 1);
    createEdge(graph, 0, 3, 4, 1);
    createEdge(graph, 0, 2, 5, 1);
    createEdge(graph, 1, 3, 3, 1);
    createEdge(graph, 2, 4, 7, 1);
    createEdge(graph, 3, 4, 6, 1);

    Route *route = dijkstra_shortestRoute(graph, 0, 4);
    unsigned int expected[] = {0, 3, 4};

    TEST_ASSERT_NOT_NULL(route);
    TEST_ASSERT_EQUAL_INT(3, route->numVertices);
    TEST_ASSERT_EQUAL_FLOAT(10, route->cost);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, route->nodes, 3);

    deleteGraph(graph);
    deleteRoute(route);
}

void dijkstra_DisconnectedVertices_ReturnsNull(void)
{
    Graph *graph = createGraph(3);

    Route *route = dijkstra_shortestRoute(graph, 0, 1);
    TEST_ASSERT_NULL(route);

    deleteGraph(graph);
    deleteRoute(route);
}

void dijkstra_InvalidEndNode_ReturnsNull(void)
{
    Graph *graph = createGraph(10);

    Route *route = dijkstra_shortestRoute(graph, 0, 11); // vertex 11 does not exist

    TEST_ASSERT_NULL(route);

    deleteGraph(graph);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(dijkstra_CorrectParameters_ReturnsShortestRoute);
    RUN_TEST(dijkstra_CorrectParameters2_ReturnsShortestRoute);
    RUN_TEST(dijkstra_DisconnectedVertices_ReturnsNull);
    RUN_TEST(dijkstra_InvalidEndNode_ReturnsNull);

    return UNITY_END();
}