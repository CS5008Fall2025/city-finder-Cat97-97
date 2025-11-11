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

// Allocates a graph with the specified number of vertices.
// Vertex names are initialized to NULL; adjacency lists start empty.
Graph *create_graph(int numVertices);
void free_graph(Graph *graph);

// Stores a copy of 'name' as the vertex name for 'index'.
void set_vertex_name(Graph *graph, int index, const char *name);

// Returns index for the given vertex name, or -1 if not found.
int find_vertex_index(const Graph *graph, const char *name);

// Adds an undirected weighted edge between u and v.
void add_undirected_edge(Graph *graph, int u, int v, int weight);

// Prints each city name on its own line in index order.
void list_cities(const Graph *graph);

#endif


