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
    createEdge(graph, 0, 1, 4, 1);
    createEdge(graph, 0, 2, 4, 1);
    createEdge(graph, 1, 2, 2, 1);
    createEdge(graph, 2, 3, 3, 1);
    createEdge(graph, 2, 4, 1, 1);
    createEdge(graph, 2, 5, 6, 1);
    createEdge(graph, 3, 5, 2, 1);
    createEdge(graph, 4, 5, 3, 1);

    Edge *path = dijkstra_shortestRoute(graph, 0, 6);
    TEST_ASSERT_NOT_NULL(path);
    TEST_ASSERT_EQUAL_INT(0, path->vertex);
    TEST_ASSERT_EQUAL_INT(2, path->next->vertex);
    TEST_ASSERT_EQUAL_INT(4, path->next->next->vertex);
    TEST_ASSERT_EQUAL_INT(5, path->next->next->next->vertex);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(dijkstra_CorrectParameters_ReturnsShortestRoute);

    return UNITY_END();
}