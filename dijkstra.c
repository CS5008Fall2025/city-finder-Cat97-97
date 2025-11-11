#include "dijkstra.h"

int dijkstra_shortest_path(const Graph *graph, int src, int dst, int **outPath, int *outPathLen, int *outTotalDistance) {
	if (graph == NULL || outPath == NULL || outPathLen == NULL || outTotalDistance == NULL) {
		return -1;
	}
	int n = graph->numVertices;
	if (src < 0 || src >= n || dst < 0 || dst >= n) {
		return -1;
	}

	int *distance = (int *)malloc((size_t)n * sizeof(int));
	int *visited = (int *)malloc((size_t)n * sizeof(int));
	int *previous = (int *)malloc((size_t)n * sizeof(int));
	if (distance == NULL || visited == NULL || previous == NULL) {
		free(distance);
		free(visited);
		free(previous);
		return -1;
	}
	for (int i = 0; i < n; i++) {
		distance[i] = INF_DISTANCE;
		visited[i] = 0;
		previous[i] = -1;
	}
	distance[src] = 0;

	// O(V^2 + E) implementation without a heap for simplicity and portability
	for (int iter = 0; iter < n; iter++) {
		int u = -1;
		int best = INF_DISTANCE;
		for (int i = 0; i < n; i++) {
			if (!visited[i] && distance[i] < best) {
				best = distance[i];
				u = i;
			}
		}
		if (u == -1) {
			break; // remaining vertices unreachable
		}
		visited[u] = 1;
		if (u == dst) {
			break;
		}
		for (Edge *e = graph->adjacency[u]; e != NULL; e = e->next) {
			int v = e->to;
			int w = e->weight;
			if (!visited[v] && distance[u] + w < distance[v]) {
				distance[v] = distance[u] + w;
				previous[v] = u;
			}
		}
	}

	if (distance[dst] >= INF_DISTANCE) {
		free(distance);
		free(visited);
		free(previous);
		return 0; // not found
	}

	// Reconstruct path from dst back to src
	int pathCapacity = 16;
	int pathSize = 0;
	int *revPath = (int *)malloc((size_t)pathCapacity * sizeof(int));
	if (revPath == NULL) {
		free(distance);
		free(visited);
		free(previous);
		return -1;
	}
	for (int cur = dst; cur != -1; cur = previous[cur]) {
		if (pathSize >= pathCapacity) {
			pathCapacity *= 2;
			int *tmp = (int *)realloc(revPath, (size_t)pathCapacity * sizeof(int));
			if (tmp == NULL) {
				free(revPath);
				free(distance);
				free(visited);
				free(previous);
				return -1;
			}
			revPath = tmp;
		}
		revPath[pathSize++] = cur;
	}

	// Reverse into output order src -> dst
	int *path = (int *)malloc((size_t)pathSize * sizeof(int));
	if (path == NULL) {
		free(revPath);
		free(distance);
		free(visited);
		free(previous);
		return -1;
	}
	for (int i = 0; i < pathSize; i++) {
		path[i] = revPath[pathSize - 1 - i];
	}

	*outPath = path;
	*outPathLen = pathSize;
	*outTotalDistance = distance[dst];

	free(revPath);
	free(distance);
	free(visited);
	free(previous);
	return 1;
}


