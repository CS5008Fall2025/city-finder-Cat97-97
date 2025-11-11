#ifndef IO_H
#define IO_H

#include "graph.h"

// Loads vertex names from the given file path.
// Returns a newly created graph in *outGraph, or NULL on failure.
// Returns 1 on success, 0 on failure.
int load_vertices(const char *verticesFilePath, Graph **outGraph);

// Loads distances of the form: city1 city2 distance
// Skips malformed lines; ignores edges with unknown cities.
// Returns 1 on success, 0 on failure.
int load_distances(Graph *graph, const char *distancesFilePath);

// Prints the help text as shown in the assignment.
void print_help(void);

#endif


