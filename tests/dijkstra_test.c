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

void dijkstra_ReturnsCorrectDistanceArray(void)
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

    float expected[] = {0, 4, 4, 7, 5, 8};
    DijkstraResult *result = dijkstra(graph, 0);

    TEST_ASSERT_EQUAL_FLOAT_ARRAY(expected, result->dist, 6);

    deleteGraph(graph);
    deleteResult(result);
}

void dijkstra_ReturnsCorrectPrecedenceArray(void)
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

    unsigned int expected[] = {-1, 0, 0, 2, 2, 4};
    DijkstraResult *result = dijkstra(graph, 0);

    TEST_ASSERT_EQUAL_INT_ARRAY(expected, result->prev, 6);

    deleteGraph(graph);
    deleteResult(result);
}

void getRoute_ReturnsCorrectRoute(void)
{
    float dist[] = {0, 4, 4, 7, 5, 8};
    unsigned int prev[] = {-1, 0, 0, 2, 2, 4};

    DijkstraResult result = { dist, prev };

    Route *route = getRoute(&result, 5);

    // The expected route
    unsigned int nodes[] = {0, 2, 4, 5};

    TEST_ASSERT_NOT_NULL(route);
    TEST_ASSERT_EQUAL_INT_ARRAY(nodes, route->nodes, 4);
    TEST_ASSERT_EQUAL_INT(4, route->numVertices);
    TEST_ASSERT_EQUAL_FLOAT(8, route->cost);

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

    RUN_TEST(dijkstra_ReturnsCorrectDistanceArray);
    RUN_TEST(dijkstra_ReturnsCorrectPrecedenceArray);
    RUN_TEST(dijkstra_DisconnectedVertices_ReturnsNull);
    RUN_TEST(dijkstra_InvalidEndNode_ReturnsNull);

    RUN_TEST(getRoute_ReturnsCorrectRoute);

    return UNITY_END();
}