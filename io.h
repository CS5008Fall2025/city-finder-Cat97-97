#ifndef IO_H
#define IO_H

#include "graph.h"

// load_vertices:
//   Loads vertex names from the given file (one per line).
//   On success, allocates and returns a Graph via outGraph.
//   Returns 1 on success, 0 on failure.
int load_vertices(const char *verticesFilePath, Graph **outGraph);

// load_distances:
//   Loads edges of the form: "city1 city2 distance".
//   Skips malformed lines and ignores edges with unknown cities.
//   Returns 1 on success, 0 on failure.
int load_distances(Graph *graph, const char *distancesFilePath);

// print_help:
//   Prints the interactive help text as specified by the assignment.
void print_help(void);

#endif


