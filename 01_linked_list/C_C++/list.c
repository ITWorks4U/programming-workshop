#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

static struct LinkedList *root = NULL;
static int node_number = 0;

void print_list(void) {
	struct LinkedList *current = root;

	do {
		puts(" **************");
		printf(" - node: %p\n - ID: %2d\n - content: %s\n - next node at: %p\n", current, current->node_id, current->data, current->next);

		current = current->next;
	} while (current != NULL);

	puts(" **************");
}

void add_to_list(char content[]) {
	if (root == NULL) {
		root = (struct LinkedList *) malloc(sizeof(struct LinkedList));
		root->node_id = node_number++;
		strncpy(root->data, content, LENGTH - 1);
		root->next = NULL;
	} else {
		struct LinkedList *current = root;

		while(current->next != NULL) {
			current = current->next;
		}

		current->next = (struct LinkedList *) malloc(sizeof(struct LinkedList));
		current = current->next;

		current->node_id = node_number++;
		strncpy(current->data, content, LENGTH - 1);
		current->next = NULL;
	}
}

void remove_from_list(int remove_key) {
	if (root == NULL) {
		fprintf(stderr, " Your list is empty.\n");
	} else {
		struct LinkedList *next_node = NULL, *tmp = NULL;

		if (root->node_id == remove_key) {
			tmp = root->next;
			free(root);
			root = tmp;
		} else {
			next_node = root;

			while (next_node->next != NULL) {
				tmp = next_node->next;

				if (tmp->node_id == remove_key) {
					next_node->next = tmp->next;
					free(tmp);
					tmp = NULL;
					break;
				}

				next_node = tmp;
			}
		}
	}
}

void reverse_list(void) {
	struct LinkedList *previous = NULL, *tmp = NULL, *current = root;

	while (current != NULL) {
		tmp = current->next;
		current->next = previous;
		previous = current;
		current = tmp;
	}

	root = previous;
}

void clear_list(void) {
	struct LinkedList *current = root;

	while (current != NULL) {
		current = current->next;
		free(root);
		root = current;
	}
}