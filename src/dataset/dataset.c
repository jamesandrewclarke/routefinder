//
// Created by James Clarke on 11/04/2021.
//

#define MAX_ARRAY_SIZE 10000
#define BUFFER_SIZE 250

#include "include/dataset.h"
#include <string.h>
#include <stdlib.h>

Dataset *ingest(FILE *file)
{
    if (file == NULL) return NULL;

    Dataset *result = malloc(sizeof(Dataset));

    result->nodes = calloc(MAX_ARRAY_SIZE, sizeof(MapNode));
    result->links = calloc(MAX_ARRAY_SIZE, sizeof(Link));

    int links = 0;
    int nodes = 0;

    char line[BUFFER_SIZE];

    while (fgets(line, BUFFER_SIZE, file))
    {
        if (strstr(line, "<link"))
        {
            Link link;
            memset(&link, 0, sizeof(Link));
            if (sscanf(line,
                       "<link id=%u node=%u node=%u way=%*u length=%f veg=%f arch=%f land=%f",
                       &link.id, &link.startId, &link.endId, &link.length, &link.veg, &link.arch, &link.land))
            {
                result->links[links] = link;
                links++;
            } else
            {
                // The file format is invalid, so we exit out
                deleteDataset(result);
                return NULL;
            }
            memset(line, 0, sizeof(char));
        }
    }

    rewind(file); // go back to the start

    while (fgets(line, BUFFER_SIZE, file))
    {
        if (strstr(line, "<node"))
        {
            MapNode node;
            memset(&node, 0, sizeof(MapNode));
            if (sscanf(line, "<node id=%u lat=%f lon=%f", &node.id, &node.lat, &node.lon))
            {
                // The dataset includes many nodes which are disconnected or not relevant to finding paths
                for (int i = 0; i < links; i++)
                {
                    // We check each link we've already parsed to check it is referenced.
                    Link *link = result->links + i;
                    if (link->startId == node.id || link->endId == node.id)
                    {
                        node.internal_id = nodes; // use an incremental ID internally
                        result->nodes[nodes] = node;
                        nodes++;
                        break;
                    }
                }
            } else
            {
                // The file format is invalid, so we exit out
                deleteDataset(result);
                return NULL;
            }
        }
    }

    result->numLinks = links;
    result->numNodes = nodes;

    return result;
}

int deleteDataset(Dataset *dataset)
{
    if (dataset == NULL) return 0;

    free(dataset->links);
    free(dataset->nodes);
    free(dataset);

    return 1;
}