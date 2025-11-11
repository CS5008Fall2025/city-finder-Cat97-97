#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"

// Constant used for "infinite" distance in Dijkstra's algorithm.
#define INF_DISTANCE 1000000000

// dijkstra_shortest_path:
//   Finds the shortest path from src to dst using Dijkstra's algorithm on an
//   adjacency-list graph. This implementation uses a linear scan to select the
//   next vertex, giving O(V^2 + E) time complexity and O(V) space.
// Parameters:
//   graph            - pointer to graph (must be non-NULL)
//   src, dst         - indices of source and destination vertices
//   outPath          - on success, receives allocated array of vertex indices
//   outPathLen       - receives number of vertices in outPath
//   outTotalDistance - receives total distance for the path
// Returns:
//   1  if a path is found (outPath/outPathLen/outTotalDistance set)
//   0  if no path exists
//  -1  on invalid input or allocation failure
int dijkstra_shortest_path(const Graph *graph, int src, int dst, int **outPath, int *outPathLen, int *outTotalDistance);

#endif


