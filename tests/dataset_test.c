//
// Created by James Clarke on 14/04/2021.
//

#include "dataset.h"
#include "unity.h"
#include <string.h>

void setUp()
{
}

void tearDown()
{
}

/**
 * Opens a file stream for a given string.
 * The dataset module takes a FILE pointer to parse a text file, but we can mock this to read from memory
 * for the purpose of unit testing.
 * This is useful as it means not having to use actual files on disk containing test strings.
 * @param string A pointer to the start of the string.
 * @return A FILE pointer.
 */
FILE *stringToStream(char *string)
{
    size_t length = strlen(string);
    FILE *fp = fmemopen(string, length, "r");

    return fp;
}

void ingest_emptyDataset_HasDefaultValues(void)
{
    char *input = " ";

    FILE *fp = stringToStream(input);

    Dataset *result = ingest(fp);
    fclose(fp);

    TEST_ASSERT_EQUAL_INT(0, result->numNodes);
    TEST_ASSERT_EQUAL_INT(0, result->numLinks);

    deleteDataset(result);
}

void ingest_ReadsCorrectNumberOfNodesAndLinks(void)
{
    char *input = "<node id=1 lat=53.802339 lon=-1.548265 /node>\n"
                  "<node id=2 lat=53.802503 lon=-1.548100 /node>\n"
                  "<node id=3 lat=53.802469 lon=-1.548017 /node>\n"
                  "<node id=4 lat=53.802507 lon=-1.547968 /node>\n"
                  "<link id=1 node=1 node=2 way=-8850 length=11.006410 veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>\n"
                  "<link id=2 node=1 node=3 way=-7726 length=11.029994 veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>\n"
                  "<link id=3 node=3 node=4 way=-7726 length=2.297085 veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>";

    FILE *fp = stringToStream(input);

    Dataset *result = ingest(fp);
    fclose(fp);

    TEST_ASSERT_EQUAL_INT(4, result->numNodes);
    TEST_ASSERT_EQUAL_INT(3, result->numLinks);

    deleteDataset(result);
}

// The dataset contains many 'dangling' nodes that don't belong to paths, these are not useful and should be ignored
void ingest_DanglingNodes_NotCounted(void)
{
    char *input = "<node id=1 lat=53.802339 lon=-1.548265 /node>\n"
                  "<node id=2 lat=53.802507 lon=-1.547968 /node>\n"
                  "<node id=3 lat=53.802507 lon=-1.547968 /node>\n" // dangling node
                  "<link id=1 node=1 node=2 way=-8850 length=11.006410 veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>";


    FILE *fp = stringToStream(input);

    Dataset *result = ingest(fp);
    fclose(fp);

    TEST_ASSERT_EQUAL_INT(2, result->numNodes);

    deleteDataset(result);
}

void ingest_ReadsCorrectValuesOfNodes(void)
{
    // The input requires a link to make sure the node isn't ignored
    char *input = "<node id=10 lat=53.802339 lon=-1.548265 /node>\n"
                  "<link id=1 node=10 node=10 way=0 length=11.006410 veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>";

    FILE *fp = stringToStream(input);

    Dataset *result = ingest(fp);
    fclose(fp);

    MapNode *node = result->nodes; // retrieve pointer to first element of array

    TEST_ASSERT_EQUAL_UINT(10, node->id);
    TEST_ASSERT_EQUAL_FLOAT(53.802339, node->lat);
    TEST_ASSERT_EQUAL_FLOAT(-1.548265, node->lon);

    deleteDataset(result);
}

void ingest_ReadsCorrectValuesOfLinks(void)
{
    char *input = "<link id=-2143392622 node=-8847 node=-8849 way=-8850 length=11.006410 veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>\n"
                  "<link id=-2143392623 node=-2560 node=-2562 way=-7726 length=11.029994 veg=0.000000 arch=0.000000 land=0.000000 POI=;/link>\n";

    FILE *fp = stringToStream(input);

    Dataset *result = ingest(fp);
    fclose(fp);

    Link expected1 = {-2143392622, -8847, -8849, (float) 11.006410, 0, 0, 0};
    Link expected2 = {-2143392623, -2560, -2562, (float) 11.029994, 0, 0, 0};

    TEST_ASSERT_EQUAL_MEMORY(&expected1, result->links + 0, sizeof(MapNode));
    TEST_ASSERT_EQUAL_MEMORY(&expected2, result->links + 1, sizeof(MapNode));

    deleteDataset(result);
}

void ingest_InvalidDataset_ReturnsNull(void)
{
    char *input = "<node i=772763242 lat=53.802339 lon=-1.548265 /node>\n";

    FILE *fp = stringToStream(input);

    Dataset *result = ingest(fp);
    fclose(fp);

    TEST_ASSERT_NULL(result);
}

int main()
{
    UNITY_BEGIN();

    RUN_TEST(ingest_emptyDataset_HasDefaultValues);
    RUN_TEST(ingest_ReadsCorrectNumberOfNodesAndLinks);
    RUN_TEST(ingest_DanglingNodes_NotCounted);
    RUN_TEST(ingest_ReadsCorrectValuesOfNodes);
    RUN_TEST(ingest_ReadsCorrectValuesOfLinks);
    RUN_TEST(ingest_InvalidDataset_ReturnsNull);

    return UNITY_END();
}
