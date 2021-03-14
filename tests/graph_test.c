//
// Created by James Clarke on 10/03/2021.
//

#define NUM_VERTICES 10

#include "unity.h"
#include "graph.h"

static Graph *graph;

void setUp(void)
{
    graph = createGraph(NUM_VERTICES);
}

void tearDown(void)
{
    deleteGraph(graph);
}

void createGraph_ReturnsPointer(void)
{
    TEST_ASSERT_NOT_NULL(graph);
}

void createGraph_InitialisesAdjacencyLists(void)
{
    for (int i = 0; i < NUM_VERTICES; i++)
    {
        AdjacencyList *adjList = graph->vertices + i;

        // There are no edges, so the head of the linked list should be null
        TEST_ASSERT_NULL(adjList->head);
        TEST_ASSERT_EQUAL(i, adjList->vertex);
    }
}

void createGraph_ContainsCorrectNumberOfVertices(void)
{
    TEST_ASSERT_EQUAL_INT(NUM_VERTICES, graph->numVertices);
}

void createGraph_ZeroVertices_ReturnsNull(void)
{
    Graph *zeroGraph = createGraph(0);

    TEST_ASSERT_NULL(zeroGraph);
}

void deleteGraph_NullGraph_Fails(void)
{
    int result = deleteGraph(NULL);

    TEST_ASSERT_NOT_EQUAL(1, result);
}

void createEdge_NullGraph_ReturnsNull(void)
{
    Edge *edge = createEdge(NULL, 2, 7, 10.2, 1);

    TEST_ASSERT_NULL(edge);
}

void createEdge_InvalidVertices_ReturnsNull(void)
{
    Edge *edge1 = createEdge(graph, NUM_VERTICES * 2, NUM_VERTICES + 3, 12, 1);
    Edge *edge2 = createEdge(graph, NUM_VERTICES - 3, NUM_VERTICES + 2, 5, 1);
    Edge *edge3 = createEdge(graph, NUM_VERTICES + 4, NUM_VERTICES - 3, 10, 1);

    TEST_ASSERT_NULL(edge1);
    TEST_ASSERT_NULL(edge2);
    TEST_ASSERT_NULL(edge3);
}

void createEdge_ValidParameters_ReturnsPointer(void)
{
    Edge *edge = createEdge(graph, 2, 3, 5, 1);

    TEST_ASSERT_NOT_NULL(edge);
}

void createEdge_ValidParameters_CreatesEdgesCorrectly(void)
{
    createEdge(graph, 2, 3, 10, 0);

    Edge *result = graph->vertices[2].head;
    TEST_ASSERT_EQUAL_INT(3, result->vertex);
    TEST_ASSERT_EQUAL_FLOAT(10, result->weight);
    TEST_ASSERT_NULL(result->next);
}

void createEdge_NotDirectional_CreatesEdgeFromEndToStart(void)
{
    createEdge(graph, 4, 5, 12, 1);

    Edge *result = graph->vertices[5].head;

    TEST_ASSERT_EQUAL_INT(4, result->vertex);
    TEST_ASSERT_EQUAL_FLOAT(12, result->weight);
    TEST_ASSERT_NULL(result->next);
}

void createEdge_EdgesAreSorted(void)
{
    createEdge(graph, 4, 5, 14, 1);
    createEdge(graph, 4, 7, 11, 1);
    createEdge(graph, 4, 7, 12, 1);
    createEdge(graph, 4, 8, 15, 1);

    Edge *result = graph->vertices[4].head;

    TEST_ASSERT_EQUAL_FLOAT(11, result->weight);
    result = result->next;

    TEST_ASSERT_EQUAL_FLOAT(12, result->weight);
    result = result->next;

    TEST_ASSERT_EQUAL_FLOAT(14, result->weight);
    result = result->next;

    TEST_ASSERT_EQUAL_FLOAT(15, result->weight);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(createGraph_ReturnsPointer);
    RUN_TEST(createGraph_ContainsCorrectNumberOfVertices);
    RUN_TEST(createGraph_ZeroVertices_ReturnsNull);
    RUN_TEST(createGraph_InitialisesAdjacencyLists);

    RUN_TEST(deleteGraph_NullGraph_Fails);

    RUN_TEST(createEdge_NullGraph_ReturnsNull);
    RUN_TEST(createEdge_InvalidVertices_ReturnsNull);
    RUN_TEST(createEdge_ValidParameters_ReturnsPointer);
    RUN_TEST(createEdge_ValidParameters_CreatesEdgesCorrectly);
    RUN_TEST(createEdge_NotDirectional_CreatesEdgeFromEndToStart);
    RUN_TEST(createEdge_EdgesAreSorted);
    return UNITY_END();
}

