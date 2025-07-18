/*
* Simple binary tree example by using C language.
*
* author:	ITWorks4U
* created:	July 14th, 2025
* updated:	July 16th, 2025
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/binary_tree.h"

static struct binary_tree *root = NULL;

struct binary_tree *get_root(void) {
	return root;
}

struct binary_tree *create_new_node(const char node_id) {
	struct binary_tree *parent = (struct binary_tree *) calloc(1, sizeof(struct binary_tree));
	parent->node_id = node_id;

	return parent;
}

bool insert_into_tree(const char node_id) {
	if (root == NULL) {
		root = create_new_node(node_id);
		return true;
	}

	struct binary_tree *current = root;
	struct binary_tree *parent = NULL;
	bool on_left_side = false;

	while (current != NULL) {
		parent = current;

		if (current->node_id < node_id) {
			/*
			* new node_id is greater than the current node_id
			* =>	go into the right side
			*/

			on_left_side = false;
			current = current->right_side;
		} else if (current->node_id > node_id) {
			/*
			* new node_id is smaller than the current node_id
			* =>	go into the left side
			*/

			on_left_side = true;
			current = current->left_side;
		} else {
			/*
			* the new node_id is equal to an already existing node
			* =>	ignore that input and leave function
			*/
			return false;
		}
	}

	if (on_left_side) {
		/*	insert a new node to the left side	*/
		parent->left_side = create_new_node(node_id);
	} else {
		/*	insert a new node to the right side	*/
		parent->right_side = create_new_node(node_id);
	}

	return true;
}

char get_minimal_node_value(void) {
	if (root == NULL) {
		return UNDEFINED_NODE;
	}

	struct binary_tree *current = root;
	while (current->left_side != NULL) {
		current = current->left_side;
	}

	return current->node_id;
}

bool delete_node(const char node_id) {
	if (root == NULL) {
		fprintf(stderr, "ERROR: %s\n", TREE_NOT_EXIST);
		return false;
	}

	struct binary_tree *current = root;
	struct binary_tree *parent = NULL;

	while(current != NULL && current->node_id != node_id) {
		parent = current;

		if (current->node_id > node_id) {
			/*	id to look for is on the left side	*/
			current = current->left_side;
		} else {
			/*	id to look for is on the right side	*/
			current = current->right_side;
		}
	}

	if (current == NULL) {
		fprintf(stderr, "node with id \"%c\" was not found in the tree\n", node_id);
		return false;
	}

	/*	3 cases to handle:	leaf, just one side, both sides	*/

	if (current->left_side != NULL && current->right_side != NULL) {
		/*
		* case 1: node to delete has a left and right sub tree
		* using in-order successor
		*/
		struct binary_tree *successor_parent = current;
		struct binary_tree *successor = current->right_side;

		while (successor->left_side != NULL) {
			successor_parent = successor;
			successor = successor->left_side;
		}

		/*	replacing current's node id with the successor's node id	*/
		current->node_id = successor->node_id;

		/*	deleting successor node	*/
		if (successor_parent->left_side == successor) {
			successor_parent->left_side = successor->right_side;
		} else {
			successor_parent->right_side = successor->right_side;
		}

		free(successor);
	} else if (current->left_side == NULL || current->right_side == NULL) {
		/*
		* case 2: this node has only one child (either left or right child)
		* save the certain sub tree of the current node
		*/
		struct binary_tree *child = current->left_side != NULL ? current->left_side : current->right_side;

		if (parent == NULL) {
			free(root);
			root = child;
		} else if (parent->left_side == current) {
			parent->left_side = child;
			free(current);
		} else {
			parent->right_side = child;
			free(current);
		}
	} else {
		/*	case 1:	no children	*/

		if (parent == NULL) {
			/*	deleting root node	*/
			free(root);
			root = NULL;
		} else if (parent->left_side == current) {
			parent->left_side = NULL;
			free(current);
		} else {
			parent->right_side = NULL;
			free(current);
		}
	}

	return true;
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

void remove_full_binary_tree(void) {
	if (root != NULL) {
		int number_of_nodes = count_number_of_nodes(root);

		/*
		* allocating a queue to handle each node to remove
		* and also ensure, that no node shall be missing during runtime
		*/
		struct binary_tree **queue = calloc(number_of_nodes, sizeof(struct binary_tree *));
		int front_side = 0, rear_side = 0;
		queue[rear_side++] = root;

		while(front_side < rear_side) {
			/*
			* idea: traverse trough each node, save the next node, left side and right side,
			* if these exists, and remove the current node from memory
			*/
			struct binary_tree *current = queue[front_side++];

			if (current->left_side != NULL) {
				queue[rear_side++] = current->left_side;
			}

			if (current->right_side != NULL) {
				queue[rear_side++] = current->right_side;
			}

			free(current);
		}

		/* no more need to use the queue for our purpose	*/
		free(queue);
		root = NULL;
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

void remove_full_binary_tree_alternative(void) {
	while(root != NULL) {
		char current_node_id = get_minimal_node_value();

		if (!delete_node(current_node_id)) {
			/*	in case of the deletion may fail	*/
			fprintf(stderr, "ERROR: Unable to remove the node ID: %c from binary tree...\nAborting removal.\n", current_node_id);
			break;
		}
	}
}

bool on_node_exists(const char node_id) {
	struct binary_tree *current = root;

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