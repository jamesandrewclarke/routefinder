//
// Created by James Clarke on 10/03/2021.
//

#include "unity.h"

void setUp(void)
{
    // who knows
}

void tearDown(void)
{
    // yes
}

void test_should_fail(void)
{
    TEST_ASSERT(0);
}

void test_should_pass(void)
{
    TEST_ASSERT(1);
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_should_fail);
    RUN_TEST(test_should_pass);
    return UNITY_END();
}