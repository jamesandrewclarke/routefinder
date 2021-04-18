#pragma once

#include "graph.h"
#include "dataset.h"

/**
 * Produces a graph from a dataset
 * @param dataset A pointer to the dataset
 * @return A pointer to the graph, returns NULL if an error occurs.
 */
Graph *datasetToGraph(Dataset* dataset);