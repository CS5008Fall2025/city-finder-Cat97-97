#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Edge {
	int to;
	int weight;
	struct Edge *next;
} Edge;

typedef struct {
	int numVertices;
	char **vertexNames;   // size numVertices
	Edge **adjacency;     // size numVertices, each a linked list
} Graph;

Graph *create_graph(int numVertices);
void free_graph(Graph *graph);

// Copies name into internal storage at index
void set_vertex_name(Graph *graph, int index, const char *name);

// Returns index of vertex name, or -1 if not found
int find_vertex_index(const Graph *graph, const char *name);

// Adds an undirected edge (u <-> v) with weight
void add_undirected_edge(Graph *graph, int u, int v, int weight);

// Lists cities to stdout, one per line, in index order
void list_cities(const Graph *graph);

#endif


