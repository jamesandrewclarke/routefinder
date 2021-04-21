//
// Created by James Clarke on 17/04/2021.
//

#include "dataset.h"
#include "graph.h"
#include "dijkstra.h"
#include "convert.h"
#include "gnuplot_i.h"

#include <stdio.h>
#include <argp.h>
#include <stdlib.h>
#include <string.h>

#define FILEPATH_BUFFER_LENGTH 50

const static char doc[] = "Route Finder - Find the optimal routes between points on a given .map file.";

const static char args_doc[] = "START END";

const static struct argp_option options[] = {
        {"file",      'f', "FILE", 0, "The .map file to read from"},
        {"visualise", 'v', 0,      0, "Visualise the map in gnuplot"},
        {0}
};

struct arguments
{
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

const static struct argp argp = {options, parse_opt, args_doc, doc};

void visualise(gnuplot_ctrl *h, Dataset *dataset, Route *route);

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
    if (arguments.file) // did the user set their own file?
    {
        filepath = arguments.filepath;
    } else
    {
        filepath = "../../data/Final_Map.map"; // default value
    }

    FILE *fp = fopen(filepath, "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error opening dataset file.\n");
        exit(1);
    }
    Dataset *result = ingest(fp);
    Graph *graph = datasetToGraph(result);

    if (result == NULL || graph == NULL)
    {
        fprintf(stderr, "Error parsing dataset.\n");
        exit(1);
    }

    printf("%i nodes with %i links read from dataset\n", result->numNodes, result->numLinks);

    if (arguments.start > result->numNodes || arguments.end > result->numNodes)
    {
        fprintf(stderr, "One of the node IDs is out of bounds for this dataset, please use numbers between 0 and %i.\n", result->numNodes);
        exit(1);
    }

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
        gnuplot_ctrl *h = gnuplot_init();
        if (h == NULL)
        {
            fprintf(stderr, "Couldn't open gnuplot, ensure it is available.\n");
            exit(1);
        }
        visualise(h, result, route);
        printf("\nPress Ctrl+D to close.\n");
        scanf(" "); // suspend the program
        gnuplot_close(h);
    }

    deleteDataset(result);
    deleteGraph(graph);
    deleteRoute(route);
}

void visualise(gnuplot_ctrl *h, Dataset *dataset, Route *route)
{
    gnuplot_cmd(h, "set terminal x11");
    gnuplot_setstyle(h, "points");
    gnuplot_set_xlabel(h, "Longitude");
    gnuplot_set_ylabel(h, "Latitude");

    double x[dataset->numNodes];
    double y[dataset->numNodes];

    for (int i = 0; i < dataset->numNodes; i++)
    {
        MapNode *node = dataset->nodes + i;

        x[i] = node->lon;
        y[i] = node->lat;
    }

    gnuplot_plot_xy(h, x, y, dataset->numNodes, "Map");

    for (int i = 0; i < dataset->numLinks; i++)
    {
        Link *link = dataset->links + i;
        MapNode *start = link->start;
        MapNode *end = link->end;

        gnuplot_cmd(h, "set arrow from %f,%f to %f,%f nohead", start->lon, start->lat, end->lon, end->lat);
    }

    for (int i = 0; i < route->numVertices - 1; i++)
    {
        unsigned int startID = route->nodes[i];
        unsigned int endID = route->nodes[i + 1];
        MapNode *start = dataset->nodes + startID;
        MapNode *end = dataset->nodes + endID;

        gnuplot_cmd(h, "set arrow from %f,%f to %f,%f lc rgb \"green\" lw 5", start->lon, start->lat, end->lon,
                    end->lat);
    }

    MapNode *source = dataset->nodes + route->nodes[0];
    MapNode *destination = dataset->nodes + route->nodes[route->numVertices - 1];

    char cmd[100];
    sprintf(cmd, "set label \"Start\" at %f,%f", source->lon, source->lat);
    gnuplot_cmd(h, cmd);
    sprintf(cmd, "set label \"End\" at %f,%f", destination->lon, destination->lat);
    gnuplot_cmd(h, cmd);

    gnuplot_cmd(h, "replot"); // this ensures the links and labels are rendered immediately
}