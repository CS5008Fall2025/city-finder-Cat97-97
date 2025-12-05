#include "graph.h"
/*
 * Graph module
 *
 * Provides a minimal adjacency-list graph for undirected, weighted edges.
 * Responsibilities:
 *  - allocate/free graphs
 *  - set and look up vertex names
 *  - add undirected edges
 *  - list city names
 */

/* 
 * duplicate_string
 * 	Create a heap-allocated copy of a C string.
 *
 * Parameters:
 * 	- source: input string (may be NULL)
 *
 * Returns:
 * 	Newly allocated null-terminated copy or NULL on error/NULL input.
 */
static char *duplicate_string(const char *source) {
	if (source == NULL) {
		return NULL;
	}
	size_t len = strlen(source);
	char *copy = (char *)malloc(len + 1);
	if (copy == NULL) {
		return NULL;
	}
	memcpy(copy, source, len + 1);
	return copy;
}

/* 
 * create_graph
 * 	Allocate a graph with space for 'numVertices' vertices. Vertex names
 * 	and adjacency lists are initialized to NULL.
 *
 * Returns:
 * 	Pointer to Graph on success; NULL on invalid input or allocation failure.
 */
Graph *create_graph(int numVertices) {
	if (numVertices <= 0) {
		return NULL;
	}
	Graph *graph = (Graph *)malloc(sizeof(Graph));
	if (graph == NULL) {
		return NULL;
	}
	graph->numVertices = numVertices;
	graph->vertexNames = (char **)calloc((size_t)numVertices, sizeof(char *));
	graph->adjacency = (Edge **)calloc((size_t)numVertices, sizeof(Edge *));
	if (graph->vertexNames == NULL || graph->adjacency == NULL) {
		free(graph->vertexNames);
		free(graph->adjacency);
		free(graph);
		return NULL;
	}
	return graph;
}

/* 
 * free_graph
 * 	Release all memory owned by the graph, including vertex names and
 * 	all adjacency lists.
 * 	Safe to call with NULL.
 */
void free_graph(Graph *graph) {
	if (graph == NULL) {
		return;
	}
	for (int i = 0; i < graph->numVertices; i++) {
		if (graph->vertexNames != NULL && graph->vertexNames[i] != NULL) {
			free(graph->vertexNames[i]);
		}
		Edge *edge = graph->adjacency != NULL ? graph->adjacency[i] : NULL;
		while (edge != NULL) {
			Edge *next = edge->next;
			free(edge);
			edge = next;
		}
	}
	free(graph->vertexNames);
	free(graph->adjacency);
	free(graph);
}

/* 
 * set_vertex_name
 * 	Assign a heap-allocated copy of 'name' to the vertex at 'index'.
 * 	Overwrites and frees any existing name.
 * 	Silently ignores out-of-range indices or NULL graph.
 */
void set_vertex_name(Graph *graph, int index, const char *name) {
	if (graph == NULL || index < 0 || index >= graph->numVertices) {
		return;
	}
	if (graph->vertexNames[index] != NULL) {
		free(graph->vertexNames[index]);
		graph->vertexNames[index] = NULL;
	}
	graph->vertexNames[index] = duplicate_string(name);
}

/* 
 * find_vertex_index
 * 	Linear search for a vertex name, returning its index or -1 if not found.
 */
int find_vertex_index(const Graph *graph, const char *name) {
	if (graph == NULL || name == NULL) {
		return -1;
	}
	for (int i = 0; i < graph->numVertices; i++) {
		if (graph->vertexNames[i] != NULL && strcmp(graph->vertexNames[i], name) == 0) {
			return i;
		}
	}
	return -1;
}

/* 
 * add_undirected_edge
 * 	Add an undirected edge (u <-> v) with 'weight'. Each direction is stored
 * 	as a separate adjacency node inserted at the head for O(1) insertion.
 * 	Ignores invalid vertex indices or NULL graph.
 */
void add_undirected_edge(Graph *graph, int u, int v, int weight) {
	if (graph == NULL) {
		return;
	}
	if (u < 0 || u >= graph->numVertices || v < 0 || v >= graph->numVertices) {
		return;
	}
	Edge *e1 = (Edge *)malloc(sizeof(Edge));
	if (e1 == NULL) {
		return;
	}
	e1->to = v;
	e1->weight = weight;
	e1->next = graph->adjacency[u];
	graph->adjacency[u] = e1;

	Edge *e2 = (Edge *)malloc(sizeof(Edge));
	if (e2 == NULL) {
		return;
	}
	e2->to = u;
	e2->weight = weight;
	e2->next = graph->adjacency[v];
	graph->adjacency[v] = e2;
}

/* 
 * list_cities
 * 	Print each non-NULL vertex name, one per line, to stdout.
 */
void list_cities(const Graph *graph) {
	if (graph == NULL) {
		return;
	}
	for (int i = 0; i < graph->numVertices; i++) {
		if (graph->vertexNames[i] != NULL) {
			printf("%s\n", graph->vertexNames[i]);
		}
	}
}


