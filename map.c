#include "map.h"
#include <stdlib.h>

Node *new_node() {
	Node *node = (Node *)malloc(sizeof(Node));
	if (node == NULL) {
		fprintf(stderr, "Memory Allocation Failed.\n");
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
	return (map_find(str + 1, node->children[(int)str[0]]));
}

int map_remove(char *str, Node *node) {
	char *parent_str = (char *)malloc(sizeof(char) * strlen(str));
	strncpy(parent_str, str, strlen(str) - 1);
	Node *parent_node_del = map_find(parent_str, node);
	if (parent_node_del == NULL) {
		return -1;
	}
	Node *node_del = parent_node_del->children[(int)str[strlen(str) - 1]];
	if (node_del == NULL) {
		return -1;
	}
	parent_node_del->children[(int)str[strlen(str) - 1]] = NULL;
	delete_node(node_del);
	free(parent_str);
	return 0;
}
