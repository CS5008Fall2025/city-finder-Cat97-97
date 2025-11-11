#include "graph.h"

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


