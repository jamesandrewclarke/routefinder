//
// Created by James Clarke on 14/04/2021.
//

#include "dataset.h"
#include <unity.h>
#include <string.h>

void setUp()
{
}

void tearDown()
{
}

void ingest_emptyDataset_HasDefaultValues(void)
{
    char *input = "";

    FILE *fp = fmemopen(input, 1, "r");

    Dataset* result = ingest(fp);

    TEST_ASSERT_EQUAL_INT(0, result->numNodes);
    TEST_ASSERT_EQUAL_INT(0, result->numLinks);

    deleteDataset(result);
    fclose(fp);
}

void ingest_ReadsCorrectNumberOfNodesAndLinks(void)
{
    char *input = "<node id=772763242 lat=53.802339 lon=-1.548265 /node>\n"
                  "<node id=772763263 lat=53.802503 lon=-1.548100 /node>\n"
                  "<node id=-2143174505 lat=53.802469 lon=-1.548017 /node>\n"
                  "<node id=-2143174532 lat=53.802507 lon=-1.547968 /node>\n"
                  "<node id=772763225 lat=53.802458 lon=-1.547826 /node>\n"
                  "<node id=772763246 lat=53.802045 lon=-1.548215 /node>\n"
                  "<node id=772763271 lat=53.802042 lon=-1.548259 /node>\n"
                  "<node id=772763230 lat=53.801892 lon=-1.548298 /node>\n"
                  "<link id=-2143392622 node=-8847 node=-8849 way=-8850 length=11.006410 veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>\n"
                  "<link id=-2143392623 node=-2560 node=-2562 way=-7726 length=11.029994 veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>\n"
                  "<link id=-2143392624 node=-2562 node=-2558 way=-7726 length=2.297085 veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>";

    unsigned long len = strlen(input);
    FILE *fp = fmemopen(input, len, "r");

    Dataset *result = ingest(fp);

    TEST_ASSERT_EQUAL_INT(8, result->numNodes);
    TEST_ASSERT_EQUAL_INT(3, result->numLinks);

    deleteDataset(result);
    fclose(fp);
}

void ingest_ReadsCorrectValuesOfNodes(void)
{
    char *input = "<node id=772763242 lat=53.802339 lon=-1.548265 /node>\n"
                  "<node id=-2143174532 lat=53.802507 lon=-1.547968 /node>\n";

    unsigned long len = strlen(input);
    FILE *fp = fmemopen(input, len, "r");

    Dataset *result = ingest(fp);

    MapNode expected1 = { 772763242, (float)53.802339, (float)-1.548265};
    MapNode expected2 = { -2143174532, (float)53.802507, (float)-1.547968 };

    TEST_ASSERT_EQUAL_MEMORY(&expected1, result->nodes + 0, sizeof(MapNode));
    TEST_ASSERT_EQUAL_MEMORY(&expected2, result->nodes + 1, sizeof(MapNode));

    deleteDataset(result);
    fclose(fp);
}

void ingest_ReadsCorrectValuesOfLinks(void)
{
    char *input = "<link id=-2143392622 node=-8847 node=-8849 way=-8850 length=11.006410 veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>\n"
                  "<link id=-2143392623 node=-2560 node=-2562 way=-7726 length=11.029994 veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>\n";

    unsigned long len = strlen(input);
    FILE *fp = fmemopen(input, len, "r");

    Dataset *result = ingest(fp);

    Link expected1 = { -2143392622 , -8847, -8849, (float)11.006410, 0, 0, 0 };
    Link expected2 = { -2143392623 , -2560, -2562, (float)11.029994, 0, 0, 0 };

    TEST_ASSERT_EQUAL_MEMORY(&expected1, result->links + 0, sizeof(MapNode));
    TEST_ASSERT_EQUAL_MEMORY(&expected2, result->links + 1, sizeof(MapNode));

    deleteDataset(result);
    fclose(fp);
}


int main()
{
    UNITY_BEGIN();

    RUN_TEST(ingest_emptyDataset_HasDefaultValues);
    RUN_TEST(ingest_ReadsCorrectNumberOfNodesAndLinks);
    RUN_TEST(ingest_ReadsCorrectValuesOfNodes);
    RUN_TEST(ingest_ReadsCorrectValuesOfLinks);

    return UNITY_END();
}