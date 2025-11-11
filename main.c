#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "io.h"
#include "dijkstra.h"

static void print_welcome(void) {
	printf("*****Welcome to the shortest path finder!******\n");
	print_help();
	printf("*******************************************************\n");
}

static void prompt(void) {
	printf("Where do you want to go today? ");
	fflush(stdout);
}

static void handle_two_cities(Graph *graph, const char *city1, const char *city2) {
	int src = find_vertex_index(graph, city1);
	int dst = find_vertex_index(graph, city2);
	if (src < 0 || dst < 0) {
		printf("Invalid Command\n");
		print_help();
		return;
	}

	int *path = NULL;
	int pathLen = 0;
	int total = 0;
	int found = dijkstra_shortest_path(graph, src, dst, &path, &pathLen, &total);
	if (found <= 0) {
		printf("Path Not Found...\n");
		free(path);
		return;
	}

	printf("Path Found...\n");
	for (int i = 0; i < pathLen; i++) {
		int idx = path[i];
		printf("\t%s\n", graph->vertexNames[idx]);
	}
	printf("Total Distance: %d\n", total);
	free(path);
}

int main(int argc, char **argv) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <vertices> <distances>\n", argv[0]);
		return 1;
	}
	const char *verticesFile = argv[1];
	const char *distancesFile = argv[2];

	Graph *graph = NULL;
	if (!load_vertices(verticesFile, &graph) || graph == NULL) {
		fprintf(stderr, "Failed to load vertices from %s\n", verticesFile);
		return 1;
	}
	if (!load_distances(graph, distancesFile)) {
		fprintf(stderr, "Failed to load distances from %s\n", distancesFile);
		free_graph(graph);
		return 1;
	}

	print_welcome();

	char input[1024];
	while (1) {
		prompt();
		if (fgets(input, sizeof(input), stdin) == NULL) {
			// EOF -> exit
			printf("Goodbye!\n");
			break;
		}
		// Strip trailing newline
		size_t len = strlen(input);
		while (len > 0 && (input[len - 1] == '\n' || input[len - 1] == '\r')) {
			input[--len] = '\0';
		}
		if (len == 0) {
			// Empty input -> treat as invalid for consistency
			printf("Invalid Command\n");
			print_help();
			continue;
		}

		// Tokenize
		char cmd[512] = {0};
		char arg1[512] = {0};
		char arg2[512] = {0};
		int tokenCount = 0;

		// Use sscanf to capture up to 3 tokens
		tokenCount = sscanf(input, "%511s %511s %511s", cmd, arg1, arg2);
		if (tokenCount == 1) {
			if (strcmp(cmd, "list") == 0) {
				list_cities(graph);
			} else if (strcmp(cmd, "help") == 0) {
				print_help();
			} else if (strcmp(cmd, "exit") == 0) {
				printf("Goodbye!\n");
				break;
			} else {
				printf("Invalid Command\n");
				print_help();
			}
		} else if (tokenCount == 2) {
			// Two city names
			handle_two_cities(graph, cmd, arg1);
		} else if (tokenCount >= 3) {
			// Too many args
			printf("Invalid Command\n");
			print_help();
		}
	}

	free_graph(graph);
	return 0;
}


