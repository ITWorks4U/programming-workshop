/*
* Simple binary tree example by using C language.
*
* author:	ITWorks4U
* created:	July 15th, 2025
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/binary_tree.h"

struct binary_tree *insert_into_tree(struct binary_tree *node, const char node_id) {
	if (node == NULL) {
		node = (struct binary_tree *) calloc(1, sizeof(struct binary_tree));
		node->node_id = node_id;

		return node;
	}

	if (node->node_id < node_id) {
		node->right_side = insert_into_tree(node->right_side, node_id);
	} else if (node->node_id > node_id) {
		node->left_side = insert_into_tree(node->left_side, node_id);
	}

	return node;
}

struct binary_tree *delete_node(struct binary_tree *node, const char node_id) {
	if (node == NULL) {
		return NULL;
	}

	/*	traversing trough the binary tree	*/
	if (node_id < node->node_id) {
		node->left_side = delete_node(node->left_side, node_id);
	} else if (node_id > node->node_id) {
		node->right_side = delete_node(node->right_side, node_id);
	} else {
		/*
		* figuring out what kind of node could exist:
		* - case 1: no child => node is a leaf
		* - case 2: one child
		* - case 3: two childs
		*/

		struct binary_tree *temp = NULL;

		if (node->left_side == NULL || node->right_side == NULL) {
			temp = node->left_side != NULL ? node->left_side : node->right_side;

			if (temp == NULL) {
				/*	case 1: leaf only	*/
				temp = node;
				node = NULL;
			} else {
				/*
				* case 2: only one child
				* copy child content into node
				*/
				*node = *temp;
			}

			free(temp);
		} else {
			/*	case 3: two childs	*/
			temp = get_minimal_node_value(node->right_side);
			node->node_id = temp->node_id;
			node->right_side = delete_node(node->right_side, temp->node_id);
		}
	}

	return node;
}

struct binary_tree *get_minimal_node_value(struct binary_tree *node) {
	struct binary_tree *current = node;

	while (current->left_side != NULL) {
		current = current->left_side;
	}

	return current;
}

void remove_full_binary_tree(struct binary_tree *node) {
	if (node != NULL) {
		remove_full_binary_tree(node->left_side);
		remove_full_binary_tree(node->right_side);
		free(node);
	}
}

void pre_order_tree(const struct binary_tree *node) {
	if (node != NULL) {
		char left_side = node->left_side != NULL ? node->left_side->node_id : PLACEHOLDER;
		char right_side = node->right_side != NULL ? node->right_side->node_id : PLACEHOLDER;

		printf(
			"current: %c\nleft: %c\nright: %c\n%s\n",
			node->node_id, left_side, right_side, SEPARATOR
		);
		pre_order_tree(node->left_side);
		pre_order_tree(node->right_side);
	}
}

void in_order_tree(const struct binary_tree *node) {
	if (node != NULL) {
		char left_side = node->left_side != NULL ? node->left_side->node_id : PLACEHOLDER;
		char right_side = node->right_side != NULL ? node->right_side->node_id : PLACEHOLDER;

		pre_order_tree(node->left_side);
		printf(
			"current: %c\nleft: %c\nright: %c\n%s\n",
			node->node_id, left_side, right_side, SEPARATOR
		);
		pre_order_tree(node->right_side);
	}
}

void post_order_tree(const struct binary_tree *node) {
	if (node != NULL) {
		char left_side = node->left_side != NULL ? node->left_side->node_id : PLACEHOLDER;
		char right_side = node->right_side != NULL ? node->right_side->node_id : PLACEHOLDER;

		pre_order_tree(node->left_side);
		pre_order_tree(node->right_side);
		printf(
			"current: %c\nleft: %c\nright: %c\n%s\n",
			node->node_id, left_side, right_side, SEPARATOR
		);
	}
}

int count_number_of_nodes(const struct binary_tree *node) {
	if (node == NULL) {
		return 0;
	}

	return 1 + count_number_of_nodes(node->left_side) + count_number_of_nodes(node->right_side);
}

void print_separator(const char *message) {
	printf("%s\n%s\n%s\n", SEPARATOR, message, SEPARATOR);
}

bool on_node_exists(struct binary_tree *node, const char node_id) {
	struct binary_tree *current = node;

	while (current != NULL) {
		if (current->node_id == node_id) {
			return true;
		}

		if (current->node_id < node_id) {
			current = current->right_side;
		} else {
			current = current->left_side;
		}
	}

	return false;
}