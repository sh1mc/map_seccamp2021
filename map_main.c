#include "map.h"
#define COMMAND_BUFFER_LENGTH 10
#define MAX_KEY_LENGTH 100

void interact();
void help();

int main() {
	interact();
	return 0;
}

void interact() {
	Node *commands = new_node();
	map_put("help", 0, commands);
	map_put("put", 1, commands);
	map_put("find", 2, commands);
	map_put("remove", 3, commands);
	map_put("list", 4, commands);
	map_put("exit", 5, commands);

	Node *map = new_node();

	printf("Type \"help\" and you can refer to the userge.\n");
	while (1) {
		char command[COMMAND_BUFFER_LENGTH];
		printf(">> ");
		char command_format[32];
		snprintf(command_format, 32, "%%%ds", COMMAND_BUFFER_LENGTH);
		scanf(command_format, command);
		for (int i = 0; i < COMMAND_BUFFER_LENGTH; i++) {
			if (command[i] == '\n') {
				command[i] = '\0';
			}
		}
		if (strcmp(command, "") == 0) continue;
		Node *command_node = map_find(command, commands);
		if (command_node == NULL) {
			printf("Invalid command.\nType \"help\" and you can refer to the userge.\n");
			continue;
		}
		int command_id = command_node->value;
		if (command_id == 0) help();
		if (command_id == 1) {
			char key[MAX_KEY_LENGTH];
			printf("key: ");
			char format[32];
			snprintf(format, 32, "%%%ds", MAX_KEY_LENGTH);
			scanf(format, key);
			int value;
			printf("value: ");
			scanf("%15d", &value);
			map_put(key, value, map);
		}
		if (command_id == 2) {
			char key[MAX_KEY_LENGTH];
			printf("key: ");
			char format[32];
			snprintf(format, 32, "%%%ds", MAX_KEY_LENGTH);
			scanf(format, key);
			Node *tgt_node = map_find(key, map);
			if (tgt_node == NULL) {
				printf("The specified key does not exist.\n");
			} else {
				printf("%s:\t%d\n", key, tgt_node->value);
			}
		}
		if (command_id == 3) {
			char key[MAX_KEY_LENGTH];
			printf("key: ");
			char format[32];
			snprintf(format, 32, "%%%ds", MAX_KEY_LENGTH);
			scanf(format, key);
			int status = map_remove(key, map);
			if (status == 0) {
				printf("Successfully deleted.\n");
			}
			if (status == -1) {
				printf("Specified key doesn't exist.\n");
			}
		}
		if (command_id == 4) {
			char buffer[MAX_KEY_LENGTH];
			strncpy(buffer, "", 2);
			map_print(buffer, MAX_KEY_LENGTH, map);
		}
		if (command_id == 5) break;
	}
	delete_node(map);
	delete_node(commands);
}

void help() {
	printf("Commands:\n");
	printf("\thelp:\tShow usage\n");
	printf("\tput:\tAdd a value to the map.\n");
	printf("\tfind:\tShow the value if the specified key exists.\n");
	printf("\tremove:\tDelete a value from the map.\n");
	printf("\tlist:\tShow the list of key and values.\n");
	printf("\texit:\tExit this program.\n");
}
