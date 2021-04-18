//
// Created by James Clarke on 18/04/2021.
//

#include "include/convert.h"

Graph *datasetToGraph(Dataset *dataset)
{
    if (dataset == NULL) return NULL;

    // Represent the dataset as a graph
    Graph *graph = createGraph(dataset->numNodes);
    // Each link must be represented as an edge on the graph
    for (int i = 0; i < dataset->numLinks; i++)
    {
        Link *link = dataset->links + i;
        unsigned int start = 0;
        unsigned int end = 0;

        // Find the IDs of the two end nodes
        for (int j = 0; j < dataset->numNodes; j++)
        {
            MapNode *node = dataset->nodes + j;
            if (node->id == link->start) {
                start = node->internal_id;
            } else if (node->id == link->end)
            {
                end = node->internal_id;
            }
        }

        if (start == 0 && end == 0) // unchanged values implies the nodes have not been found
        {
            return NULL;
        } else {
            createEdge(graph, start, end, link->length, 1);
        }
    }

    return graph;
}