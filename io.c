#include "io.h"

static int count_lines_in_file(const char *filePath) {
	FILE *fp = fopen(filePath, "r");
	if (fp == NULL) {
		return -1;
	}
	int count = 0;
	char buffer[1024];
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		// Count non-empty lines
		// Trim newline
		char *p = buffer;
		while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') {
			p++;
		}
		if (*p != '\0') {
			count++;
		}
	}
	fclose(fp);
	return count;
}

int load_vertices(const char *verticesFilePath, Graph **outGraph) {
	if (outGraph == NULL || verticesFilePath == NULL) {
		return 0;
	}
	*outGraph = NULL;
	int count = count_lines_in_file(verticesFilePath);
	if (count <= 0) {
		return 0;
	}
	Graph *graph = create_graph(count);
	if (graph == NULL) {
		return 0;
	}

	FILE *fp = fopen(verticesFilePath, "r");
	if (fp == NULL) {
		free_graph(graph);
		return 0;
	}
	char buffer[1024];
	int index = 0;
	while (index < count && fgets(buffer, sizeof(buffer), fp) != NULL) {
		// Strip trailing newline
		size_t len = strlen(buffer);
		while (len > 0 && (buffer[len - 1] == '\n' || buffer[len - 1] == '\r')) {
			buffer[--len] = '\0';
		}
		// Skip empty lines
		if (len == 0) {
			continue;
		}
		set_vertex_name(graph, index, buffer);
		index++;
	}
	fclose(fp);
	*outGraph = graph;
	return 1;
}

int load_distances(Graph *graph, const char *distancesFilePath) {
	if (graph == NULL || distancesFilePath == NULL) {
		return 0;
	}
	FILE *fp = fopen(distancesFilePath, "r");
	if (fp == NULL) {
		return 0;
	}
	char buffer[1024];
	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		// Format: city1 city2 distance
		// Skip empty or whitespace-only lines
		char *line = buffer;
		while (*line == ' ' || *line == '\t' || *line == '\r' || *line == '\n') {
			line++;
		}
		if (*line == '\0') {
			continue;
		}

		// Tokenize by spaces
		char city1[512];
		char city2[512];
		int dist = 0;
		int scanned = sscanf(line, "%511s %511s %d", city1, city2, &dist);
		if (scanned != 3) {
			// Skip malformed lines
			continue;
		}
		int u = find_vertex_index(graph, city1);
		int v = find_vertex_index(graph, city2);
		if (u < 0 || v < 0) {
			// Unknown city name; ignore per safe assumptions
			continue;
		}
		add_undirected_edge(graph, u, v, dist);
	}
	fclose(fp);
	return 1;
}

void print_help(void) {
	printf("Commands:\n");
	printf("\tlist - list all cities\n");
	printf("\t<city1> <city2> - find the shortest path between two cities\n");
	printf("\thelp - print this help message\n");
	printf("\texit - exit the program\n");
}


