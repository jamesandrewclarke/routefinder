//
// Created by James Clarke on 10/03/2021.
//

#include "unity.h"
#include "graph.h"

Graph *graph;

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

int main()
{
    UNITY_BEGIN();
    RUN_TEST(createGraph_HasNullHeads);
    RUN_TEST(createGraph_ReturnsPointer);

    RUN_TEST(addNode_NullGraph_ReturnsNull);
    RUN_TEST(addNode_DuplicateID_ReturnsNull);
    RUN_TEST(addNode_SetsGraphHeadToNewNode);

    RUN_TEST(findNode_NullGraph_ReturnsNull);
    RUN_TEST(findNode_NonexistentID_ReturnsNull);
    RUN_TEST(findNode_KnownID_ReturnsPointer);
    return UNITY_END();
}

