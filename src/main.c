//
// Created by James Clarke on 17/04/2021.
//

#include "dataset.h"
#include "graph.h"
#include "dijkstra.h"
#include "gnuplot_i.h"

#include <stdio.h>
#include <argp.h>
#include <stdlib.h>
#include <string.h>

#define FILEPATH_BUFFER_LENGTH 50

const static char doc[] = "Route Finder - Find the optimal routes between points on a given .map file.";

const static char args_doc[] = "START END";

const static struct argp_option options[] = {
        {"file", 'f', "FILE", 0, "The .map file to read from"},
        {"visualise", 'v', 0, 0, "Visualise the map in gnuplot"},
        { 0 }
};

struct arguments {
    unsigned int start;
    unsigned int end;
    int visualise;
    int file;
    char filepath[FILEPATH_BUFFER_LENGTH];
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
    struct arguments *arguments = state->input;

    switch (key)
    {
        case 'v':
            arguments->visualise = 1;
            break;

        case 'f':
            strcpy(arguments->filepath, arg);
            arguments->file = 1; // indicates the file has been set
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
    arguments.file = 0;

    // Use argp to parse the input and fill out the result in our arguments struct
    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    char *filepath;
    if (!arguments.file) // did the user set their own file?
    {
        filepath = "../../data/Final_Map.map"; // default value
    } else
    {
        filepath = arguments.filepath;
    }

    FILE *fp = fopen(filepath, "r");
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
        exit(1);
    }

    printf("Route: ");
    for (int i = 0; i < route->numVertices; i++)
    {
        printf("%i, ", route->nodes[i]);
    }

    if (arguments.visualise)
    {
        printf("\nInitialising gnuplot...\n");
        gnuplot_ctrl *h = gnuplot_init();
        if (h == NULL)
        {
            fprintf(stderr, "Couldn't open gnuplot, ensure it is available.\n");
            exit(1);
        }

        gnuplot_cmd(h, "set terminal qt");
        gnuplot_setstyle(h, "points");
        gnuplot_set_xlabel(h, "Longitude");
        gnuplot_set_ylabel(h, "Latitude");

        double x[result->numNodes];
        double y[result->numNodes];

        for (int i = 0; i < result->numNodes; i++)
        {
            MapNode *node = result->nodes + i;

            x[i] = node->lon;
            y[i] = node->lat;
        }

        gnuplot_plot_xy(h, x, y, result->numNodes, "Map");

        for (int i = 0; i < result->numLinks; i++)
        {
            Link *link = result->links + i;

            MapNode *start;
            MapNode *end;
            for (int j = 0; j < result->numNodes; j++)
            {
                MapNode *node = result->nodes + j;

                if (node->id == link->start)
                {
                    start = node;
                } else if (node->id == link->end)
                {
                    end = node;
                }
            }

            gnuplot_cmd(h, "set arrow from %f,%f to %f,%f nohead", start->lon, start->lat, end->lon, end->lat);
        }

        for (int i = 0; i < route->numVertices - 1; i++)
        {
            unsigned int startID = route->nodes[i];
            unsigned int endID = route->nodes[i+1];
            MapNode *start = result->nodes + startID;
            MapNode *end = result->nodes + endID;

            gnuplot_cmd(h, "set arrow from %f,%f to %f,%f lc rgb \"green\" lw 5", start->lon, start->lat, end->lon, end->lat);
        }

        printf("\nPress Ctrl+D to close.\n");
        scanf(" "); // suspend the program
        gnuplot_close(h);
    }

    deleteDataset(result);
    deleteGraph(graph);
    deleteRoute(route);
}