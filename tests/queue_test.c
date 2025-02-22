//
// Created by James Clarke on 04/04/2021.
//

#include "queue.h"
#include "unity.h"
#include <stdlib.h>

static PriorityQueue *Q;

void setUp()
{
    Q = createQueue();
}

void tearDown()
{
    deleteQueue(Q);
}

void createQueue_ReturnsPointer(void)
{
    TEST_ASSERT_NOT_NULL(Q);
}

void createNode_ReturnsPointer(void)
{
    Node *new = createNode(0, 100);

    TEST_ASSERT_NOT_NULL(new);

    free(new);
}

void addWithPriority_ValidParameters_Succeeds(void)
{
    int result = addWithPriority(Q, 0, 10);

    TEST_ASSERT_EQUAL_INT(1, result);
}

void addWithPriority_NullQueue_Fails(void)
{
    int result = addWithPriority(NULL, 0, 5);

    TEST_ASSERT_EQUAL_INT(0, result);
}

void addWithPriority_ValidParameters_AddsToQueue(void)
{
    addWithPriority(Q, 0, 7);

    TEST_ASSERT_EQUAL_INT(0, Q->head->id);
    TEST_ASSERT_EQUAL_FLOAT(7, Q->head->priority);
}

void addWithPriority_MultipleElements_AddsInOrder(void)
{
    addWithPriority(Q, 2, 7);
    addWithPriority(Q, 0, 3);
    addWithPriority(Q, 1, 10);

    Node *sample;
    // 1st
    sample = Q->head;
    TEST_ASSERT_EQUAL_INT(0, sample->id);
    TEST_ASSERT_EQUAL_FLOAT(3, sample->priority);

    // 2nd
    sample = sample->next;
    TEST_ASSERT_EQUAL_INT(2, sample->id);
    TEST_ASSERT_EQUAL_FLOAT(7, sample->priority);

    // 3rd
    sample = sample->next;
    TEST_ASSERT_EQUAL_INT(1, sample->id);
    TEST_ASSERT_EQUAL_FLOAT(10, sample->priority);
}

void removeFromQueue_NullQueue_Fails(void)
{
    int result = removeFromQueue(NULL, 0);

    TEST_ASSERT_EQUAL_INT(0, result);
}

void removeFromQueue_NonexistentElement_Fails(void)
{
    addWithPriority(Q, 0, 5);
    int result = removeFromQueue(Q, 1);

    TEST_ASSERT_EQUAL_INT(0, result);
}

void removeFromQueue_ValidElement_Succeeds(void)
{
    addWithPriority(Q, 0, 3);
    int result = removeFromQueue(Q, 0);

    TEST_ASSERT_EQUAL_INT(1, result);
}

void removeFromQueue_ValidElement_RemovesFromQueue(void)
{
    addWithPriority(Q, 0, 3);
    addWithPriority(Q, 1, 6);
    addWithPriority(Q, 2, 7);
    removeFromQueue(Q, 1);

    Node *sample;

    // 1st
    sample = Q->head;
    TEST_ASSERT_EQUAL_INT(0, sample->id);
    TEST_ASSERT_EQUAL_FLOAT(3, sample->priority);

    // 2nd
    sample = sample->next;
    TEST_ASSERT_EQUAL_INT(2, sample->id);
    TEST_ASSERT_EQUAL_FLOAT(7, sample->priority);
}

void queueIsEmpty_EmptyQueue_ReturnsTrue(void)
{
    TEST_ASSERT_EQUAL_INT(1, queueIsEmpty(Q));
}

void queueIsEmpty_NonEmptyQueue_ReturnsFalse(void)
{
    addWithPriority(Q, 1, 10);

    TEST_ASSERT_EQUAL_INT(0, queueIsEmpty(Q));
}

void extractMin_PopulatedQueue_ReturnsSmallestElement(void)
{
    addWithPriority(Q, 0, 5);
    addWithPriority(Q, 1, 3);
    addWithPriority(Q, 2, 7);
    Node min = extractMin(Q);

    TEST_ASSERT_EQUAL_INT(3, min.priority);
    TEST_ASSERT_EQUAL_INT(1, min.id);
}

void extractMin_PopulatedQueue_ReturnsElementsInOrder(void)
{
    addWithPriority(Q, 0, 11);
    addWithPriority(Q, 1, 7);
    addWithPriority(Q, 2, 5);

    Node min;
    // 1st
    min = extractMin(Q);
    TEST_ASSERT_EQUAL_INT(5, min.priority);
    TEST_ASSERT_EQUAL_INT(2, min.id);

    // 2nd
    min = extractMin(Q);
    TEST_ASSERT_EQUAL_INT(7, min.priority);
    TEST_ASSERT_EQUAL_INT(1, min.id);

    // 3rd
    min = extractMin(Q);
    TEST_ASSERT_EQUAL_INT(11, min.priority);
    TEST_ASSERT_EQUAL_INT(0, min.id);
}

void changePriority_NullQueue_ReturnsFalse(void)
{
    int result = changePriority(NULL, 0, 10);

    TEST_ASSERT_EQUAL_INT(0, result);
}

void changePriority_ValidParameters_ReturnsTrue(void)
{
    addWithPriority(Q, 0, 3);

    int result = changePriority(Q, 0, 4);

    TEST_ASSERT_EQUAL_INT(1, result);
}

void changePriority_ValidParameters_ChangesPriority(void)
{
    addWithPriority(Q, 0, 3);

    changePriority(Q, 0, 4);

    TEST_ASSERT_EQUAL_INT(4, Q->head->priority);
}

void extractMin_NullQueue_Fails(void)
{
    Node min = extractMin(NULL);

    TEST_ASSERT_EQUAL_INT(-1, min.id);
}

void extractMin_EmptyQueue_Fails(void)
{
    Node min = extractMin(Q);

    TEST_ASSERT_EQUAL_INT(-1, min.id);
}


int main()
{
    UNITY_BEGIN();

    RUN_TEST(createQueue_ReturnsPointer);

    RUN_TEST(createNode_ReturnsPointer);

    RUN_TEST(queueIsEmpty_EmptyQueue_ReturnsTrue);
    RUN_TEST(queueIsEmpty_NonEmptyQueue_ReturnsFalse);

    RUN_TEST(addWithPriority_ValidParameters_Succeeds);
    RUN_TEST(addWithPriority_NullQueue_Fails);
    RUN_TEST(addWithPriority_ValidParameters_AddsToQueue);
    RUN_TEST(addWithPriority_MultipleElements_AddsInOrder);

    RUN_TEST(removeFromQueue_NullQueue_Fails);
    RUN_TEST(removeFromQueue_NonexistentElement_Fails);
    RUN_TEST(removeFromQueue_ValidElement_Succeeds);
    RUN_TEST(removeFromQueue_ValidElement_RemovesFromQueue);

    RUN_TEST(changePriority_NullQueue_ReturnsFalse);
    RUN_TEST(changePriority_ValidParameters_ReturnsTrue);
    RUN_TEST(changePriority_ValidParameters_ChangesPriority);

    RUN_TEST(extractMin_NullQueue_Fails);
    RUN_TEST(extractMin_EmptyQueue_Fails);
    RUN_TEST(extractMin_PopulatedQueue_ReturnsSmallestElement);
    RUN_TEST(extractMin_PopulatedQueue_ReturnsElementsInOrder);

    return UNITY_END();
}