//
// Created by James Clarke on 17/04/2021.
//

#include "dataset.h"
#include "graph.h"
#include "dijkstra.h"

#include <stdio.h>
#include <argp.h>
#include <stdlib.h>

const static char doc[] = "Route Finder - Find the optimal routes between points on a given .map file.";

const static char args_doc[] = "START END";

const static struct argp_option options[] = {
        {"visualise", 'v', 0, 0, "Visualise the map in gnuplot"},
        { 0 }
};

struct arguments {
    unsigned int start;
    unsigned int end;
    int visualise;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;

    switch (key)
    {
        case 'v':
            arguments->visualise = 1;
            break;
        case ARGP_KEY_ARG:
            if (state->arg_num > 2) // too many arguments
            {
                argp_usage(state);
                break;
            }
            unsigned int result = strtoul(arg, 0, 10);

            switch (state->arg_num)
            {
                case 0:
                    arguments->start = result;
                    break;
                case 1:
                    arguments->end = result;
                    break;
                default:
                   return ARGP_ERR_UNKNOWN;
            }

            break;

        case ARGP_KEY_END:
            if (state->arg_num < 2) // too few arguments
            {
                argp_usage(state);
                break;
            }

        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

const static struct argp argp = { options, parse_opt, args_doc, doc };

int main(int argc, char **argv)
{
    // Set default values
    struct arguments arguments;
    arguments.start = 0;
    arguments.end = 0;
    arguments.visualise = 0;

    // Use argp to parse the input and fill out the result in our arguments struct
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    FILE *fp = fopen("../../data/Final_Map.map", "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error opening dataset file.\n");
        exit(1);
    }
    Dataset *result = ingest(fp);

    if (result == NULL)
    {
        fprintf(stderr, "Error parsing dataset.\n");
        exit(1);
    }

    // Represent the dataset as a graph
    Graph *graph = createGraph(result->numNodes);
    // Each link must be represented as an edge on the graph
    for (int i = 0; i < result->numLinks; i++)
    {
        Link *link = result->links + i;
        unsigned int start = 0;
        unsigned int end = 0;

        // Find the IDs of the two end nodes
        for (int j = 0; j < result->numNodes; j++)
        {
            MapNode *node = result->nodes + j;
            if (node->id == link->start) {
                start = node->internal_id;
            } else if (node->id == link->end)
            {
                end = node->internal_id;
            }
        }

        if (start == 0 && end == 0) // unchanged values implies the nodes have not been found
        {
            fprintf(stderr, "Error creating edges on the graph.\n");
        } else {
            createEdge(graph, start, end, link->length, 1);
        }
    }

    // TODO extract the dataset conversion to a library or function, so it can be used in integration tests

    Route *route = dijkstra_shortestRoute(graph, arguments.start, arguments.end);
    if (route != NULL)
    {
        printf("Total Nodes: %i\n", route->numVertices);
        printf("Length: %f\n", route->cost);
    } else
    {
        fprintf(stderr, "A route could not be found between these nodes.\n");
    }

    printf("Route: ");
    for (int i = 0; i < route->numVertices; i++)
    {
        printf("%i, ", route->nodes[i]);
    }

    printf("\n");

    deleteDataset(result);
    deleteGraph(graph);
    deleteRoute(route);
}