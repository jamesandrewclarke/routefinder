//
// Created by James Clarke on 11/04/2021.
//

#define MAX_ARRAY_SIZE 10000

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

    char line[100];

    while (fgets(line, 100, file)) {
        if (strstr(line, "<node")) {

            MapNode node;
            memset(&node, 0, sizeof(MapNode));
            if (sscanf(line, "<node id=%u lat=%f lon=%f", &node.id, &node.lat, &node.lon))
            {
                result->nodes[nodes] = node;
                nodes++;
            }

        } else if (strstr(line, "<link")) {
            Link link;
            memset(&link, 0, sizeof(Link));
            if (sscanf(line,
                       "<link id=%u node=%u node=%u way=* length=%f veg=%f arch=%f land=%f",
                       &link.id, &link.start, &link.end, &link.length, &link.veg, &link.arch, &link.land ))
            {
                result->links[links] = link;
                links++;
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