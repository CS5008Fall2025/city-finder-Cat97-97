#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"

// Returns 1 if path found, 0 if not found, -1 on error.
// Allocates *outPath with length *outPathLen, containing vertex indices from src to dst inclusive.
// Sets *outTotalDistance to the total weight on the path if found.
int dijkstra_shortest_path(const Graph *graph, int src, int dst, int **outPath, int *outPathLen, int *outTotalDistance);

#endif


