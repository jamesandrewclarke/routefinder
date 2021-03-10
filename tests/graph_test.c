//
// Created by James Clarke on 10/03/2021.
//

#include "unity.h"
#include "graph.h"

static Graph *graph;

void setUp(void)
{
    graph = createGraph();
}

void tearDown(void)
{
    deleteGraph(graph);
}

void createGraph_ReturnsPointer(void)
{
    TEST_ASSERT_NOT_NULL(graph);
}

void createGraph_HasNullHeads(void)
{
    TEST_ASSERT_NULL(graph->edgeHead);
    TEST_ASSERT_NULL(graph->nodeHead);
}

void deleteGraph_NullGraph_Fails(void)
{
    int result = deleteGraph(NULL);

    TEST_ASSERT_NOT_EQUAL(1, result);
}

void addNode_NullGraph_ReturnsNull(void)
{
    Node *node = addNode(NULL, 10);

    TEST_ASSERT_NULL(node);
}

void addNode_DuplicateID_ReturnsNull(void)
{
    Node *first = addNode(graph, 10);
    Node *second = addNode(graph, 10);

    TEST_ASSERT_NOT_NULL(first);
    TEST_ASSERT_NULL(second);
}

void addNode_ValidParameters_Successful(void)
{
    const int id = 55;
    Node *new = addNode(graph, id);

    TEST_ASSERT_EQUAL_INT(id, new->id);
}

void addNode_SetsGraphHeadToNewNode(void)
{
    Node *new = addNode(graph, 100);

    TEST_ASSERT_EQUAL(new, graph->nodeHead);
}

void findNode_NullGraph_ReturnsNull(void)
{
    Node *result = findNode(NULL, 1000);

    TEST_ASSERT_NULL(result);
}

void findNode_NonexistentID_ReturnsNull(void)
{
    Node *result = findNode(graph, 1000);

    TEST_ASSERT_NULL(result);
}

void findNode_KnownID_ReturnsPointer(void)
{
    int id = 10;
    Node *node = addNode(graph, id);

    Node *result = findNode(graph, id);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL(node, result);
}

void deleteNode_NullGraph_Fails(void)
{
    int result = deleteNode(NULL, NULL);

    TEST_ASSERT_NOT_EQUAL(1, result);
}

void deleteNode_UnknownNode_Fails(void)
{
    int result = deleteNode(graph, NULL);

    TEST_ASSERT_NOT_EQUAL(1, result);
}

void deleteNode_KnownNode_Succeeds(void)
{
    Node *node = addNode(graph, 100);

    int result = deleteNode(graph, node);

    TEST_ASSERT_EQUAL(1, result);
}

void addEdge_NullGraph_ReturnsNull(void)
{
    Edge *edge = addEdge(NULL, NULL, NULL, 0);

    TEST_ASSERT_NULL(edge);
}

void addEdge_NullConnectingNodes_ReturnsNull(void)
{
    Edge *edge = addEdge(graph, NULL, NULL, 0);

    TEST_ASSERT_NULL(edge);
}

void deleteEdge_NullGraph_Fails(void)
{
    int result = deleteEdge(NULL, NULL);

    TEST_ASSERT_NOT_EQUAL(1, result);
}

void deleteEdge_ValidEdge_Succeeds(void)
{
    Node *first = addNode(graph, 1);
    Node *second = addNode(graph, 2);
    Edge *edge = addEdge(graph, first, second, 100);

    int result = deleteEdge(graph, edge);

    TEST_ASSERT_EQUAL(1, result);
}

void deleteEdge_InvalidEdge_Fails(void)
{
    // Create a valid edge, but in another graph
    Graph *otherGraph = createGraph();
    Node *first = addNode(otherGraph, 1);
    Node *second = addNode(otherGraph, 2);
    Edge *edge = addEdge(otherGraph, first, second, 100);

    // Attempt to delete this from in the main graph
    int result = deleteEdge(graph, edge);

    deleteGraph(otherGraph);

    TEST_ASSERT_NOT_EQUAL(result, 1);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(createGraph_HasNullHeads);
    RUN_TEST(createGraph_ReturnsPointer);

    RUN_TEST(deleteGraph_NullGraph_Fails);

    RUN_TEST(addNode_NullGraph_ReturnsNull);
    RUN_TEST(addNode_DuplicateID_ReturnsNull);
    RUN_TEST(addNode_SetsGraphHeadToNewNode);
    RUN_TEST(addNode_ValidParameters_Successful);

    RUN_TEST(findNode_NullGraph_ReturnsNull);
    RUN_TEST(findNode_NonexistentID_ReturnsNull);
    RUN_TEST(findNode_KnownID_ReturnsPointer);

    RUN_TEST(deleteNode_NullGraph_Fails);
    RUN_TEST(deleteNode_UnknownNode_Fails);
    RUN_TEST(deleteNode_KnownNode_Succeeds);

    RUN_TEST(addEdge_NullConnectingNodes_ReturnsNull);
    RUN_TEST(addEdge_NullGraph_ReturnsNull);

    RUN_TEST(deleteEdge_InvalidEdge_Fails);
    RUN_TEST(deleteEdge_NullGraph_Fails);
    RUN_TEST(deleteEdge_ValidEdge_Succeeds);
    return UNITY_END();
}

