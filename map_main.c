#include "map.h"

int main() {
	Node *map = new_node();
	map_put("abc", 46, map);
	map_put("abd", 10, map);
	map_put("amd", 20, map);
	map_put("md", 30, map);
	char *buf = (char *)malloc(sizeof(char) * 100);
	map_print(buf, 100, map);
	printf("%d\n", map_find("abc", map)->value);
	printf("%d\n", map_find("amd", map)->value);
	printf("address: 0x%016lx\n", (long)map_find("amd", map));
	printf("address: 0x%016lx\n", (long)map_find("abd", map));
	if (map_find("a", map) == NULL) {
		printf("key \"a\" is not found\n");
	}
	printf("%d\n", map_remove("md", map));
	printf("%d\n", map_remove("mda", map));
	delete_node(map);
	return 0;
}
