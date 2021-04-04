//
// Created by James Clarke on 04/04/2021.
//

#include "queue.h"
#include "unity.h"

void setUp()
{
}

void tearDown()
{
}

void queueIsEmpty_EmptyQueue_ReturnsTrue(void)
{
    PriorityQueue *Q = createQueue();

    TEST_ASSERT_EQUAL_INT(1, queueIsEmpty(Q));
}

void queueIsEmpty_NonEmptyQueue_ReturnsFalse(void)
{
    PriorityQueue *Q = createQueue();

    addWithPriority(Q, 1, 10);

    TEST_ASSERT_EQUAL_INT(0, queueIsEmpty(Q));
}


int main()
{
    UNITY_BEGIN();

    RUN_TEST(queueIsEmpty_EmptyQueue_ReturnsTrue);
    RUN_TEST(queueIsEmpty_NonEmptyQueue_ReturnsFalse);

    return UNITY_END();
}