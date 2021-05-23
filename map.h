#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHILDREN_SIZE 0x100

typedef struct node Node;
struct node {
	Node *children[CHILDREN_SIZE];
	int value;
};

Node *new_node();
void init_node(Node *node);
void delete_node(Node *node);

void map_put(char *str, int value, Node *node);
Node *map_find(char *str, Node *node);
int map_remove(char *str, Node *node);

#endif
