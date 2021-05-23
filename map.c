#include "map.h"
#include <stdlib.h>

Node *new_node() {
	Node *node = (Node *)malloc(sizeof(Node));
	if (node == NULL) {
		fprintf(stderr, "Memory allocation failed.\n");
		exit(EXIT_FAILURE);
	}
	init_node(node);
	return node;
}

void init_node(Node *node) {
	for (int i = 0; i < CHILDREN_SIZE; i++) {
		node->children[i] = NULL;
	}
	node->value = 0;
}

void delete_node(Node *node) {
	for (int i = 0; i < CHILDREN_SIZE; i++) {
		if (node->children[i] != NULL) {
			delete_node(node->children[i]);
		}
	}
	free(node);
}

void map_put(char *str, int value, Node *node) {
	if (node->children[(int)str[0]] == NULL) {
		node->children[(int)str[0]] = new_node();
	}
	if (str[0] == '\0') {
		if (node->children[(int)str[0]] == NULL) {
			node->children[(int)str[0]] = new_node();
		}
		node->children[(int)str[0]]->value = value;
		return;
	}
	map_put(str + 1, value, node->children[(int)str[0]]);
}

Node *map_find(char *str, Node *node) {
	if (node->children[(int)str[0]] == NULL) {
		return NULL;
	}
	if (str[0] == '\0') {
		return node->children[(int)str[0]];
	}
	return map_find(str + 1, node->children[(int)str[0]]);
}

int map_remove(char *str, Node *node) {
	if (node->children[(int)str[0]] == NULL) {
		return -1;
	}
	if (str[0] == '\0') {
		free(node->children[(int)str[0]]);
		node->children[(int)str[0]] = NULL;
		return 0;
	}
	return map_remove(str + 1, node->children[(int)str[0]]);
}

/* ------------------------------------------
*str needs to be longer than the longest key. 
buffer_length is the size of *str.
------------------------------------------ */
void map_print(char *str, int buffer_length, Node *node) {
	if (node->children[(int)'\0'] != NULL) {
		printf("%s\n", str);
	}
	for (int i = 0; i < CHILDREN_SIZE; i++) {
		if (node->children[i] != NULL) {
			char *cpy_buffer = (char *)malloc(sizeof(char) * buffer_length);
			if (cpy_buffer == NULL) {
				fprintf(stderr, "Memory allocation failed.\n");
			}
			strncpy(cpy_buffer, str, buffer_length);
			snprintf(cpy_buffer, buffer_length, "%s%c", str, (char)i);
			map_print(cpy_buffer, buffer_length, node->children[i]);
			free(cpy_buffer);
		}
	}
}
