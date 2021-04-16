#pragma once

#include <stdio.h>

typedef struct Dataset Dataset;
typedef struct MapNode MapNode;
typedef struct Link Link;

struct MapNode
{
    unsigned int internal_id;
    unsigned int id;
    float lat;
    float lon;
};

struct Link
{
    unsigned int id;
    unsigned int start;
    unsigned int end;
    float length;
    float veg;
    float arch;
    float land;
};

struct Dataset
{
    int numNodes;
    MapNode *nodes;
    int numLinks;
    Link *links;
};

/**
 * Parses a .map file
 * @param file A file stream to be read from
 * @return A pointer to a dataset struct, null if error occurs.
 */
Dataset *ingest(FILE *file);

/**
 * Frees memory used by a dataset
 * @param dataset The dataset to be freed
 * @return A status code, 1 if successful
 */
int deleteDataset(Dataset *dataset);