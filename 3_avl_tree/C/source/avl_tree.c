/*
* Using an AVL tree in C language.
*
* author:	ITWorks4U
* created:	July 16th, 2025
*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/avl_tree.h"

struct avl_tree* insert_into_avl_tree(struct avl_tree* node, const char node_id) {
	if (node == NULL) {
		/*	the height of a newly created node is always 0	*/
		node = (struct avl_tree *) calloc(1, sizeof(struct avl_tree));
		node->node_id = node_id;

		return node;
	}

	if (node_id < node->node_id) {
		node->left_side = insert_into_avl_tree(node->left_side, node_id);
	} else if (node_id > node->node_id) {
		node->right_side = insert_into_avl_tree(node->right_side, node_id);
	} else {
		/*	no douplicates are allowed	*/
		return node;
	}

	node->height = MAX_VALUE(get_tree_height(node->left_side), get_tree_height(node->right_side)) + 1;
	int balance_factor = get_balance_factor(node);

	/*	check, if a rotation to the left or right is going to do	*/

	/*	single rotation	*/
	if (balance_factor > 1 && node_id < node->left_side->node_id) {
		return rotate_right(node);
	}

	if (balance_factor < -1 && node_id > node->right_side->node_id) {
		return rotate_left(node);
	}

	/*	double rotation	*/
	if (balance_factor > 1 && node_id > node->left_side->node_id) {
		node->left_side = rotate_left(node->left_side);
		return rotate_right(node);
	}

	if (balance_factor < -1 && node_id < node->right_side->node_id) {
		node->right_side = rotate_right(node->right_side);
		return rotate_left(node);
	}

	return node;
}

struct avl_tree * get_minimal_node_value(struct avl_tree* node) {
	if (node == NULL) {
		return NULL;
	}

	struct avl_tree *current = node;
	while (current->left_side != NULL) {
		current = current->left_side;
	}

	return current;
}

struct avl_tree* delete_node(struct avl_tree* node, const char node_id) {
	if (node == NULL) {
		return NULL;
	}

	if (node_id < node->node_id) {
		node->left_side = delete_node(node->left_side, node_id);
	} else if (node_id > node->node_id) {
		node->right_side = delete_node(node->right_side, node_id);
	} else {
		struct avl_tree *temp = NULL;

		if((node->left_side == NULL) || (node->right_side == NULL)) {
			temp = node->left_side ? node->left_side : node->right_side; 

			if (temp == NULL) { 
				temp = node;
				node = NULL;
			} else {
				*node = *temp;
			}

			free(temp); 
		} else {
			temp = get_minimal_node_value(node->right_side);
			node->node_id = temp->node_id;
			node->right_side = delete_node(node->right_side, temp->node_id); 
		}
	}

	/*	check against NULL, because the NULL check at the begin is different by recursion	*/
	if (node == NULL) {
		return NULL;
	}

	/*	rotations, if required	*/

	node->height = MAX_VALUE(get_tree_height(node->left_side), get_tree_height(node->right_side)) + 1;
	int balance_factor = get_balance_factor(node);

	/*	single rotations	*/
	if (balance_factor > 1 && get_balance_factor(node->left_side) >= 0) {
		return rotate_right(node->right_side);
	}

	if (balance_factor < -1 && get_balance_factor(node->right_side) <= 0) {
		return rotate_left(node->left_side);
	}

	/*	double rotations	*/
	if (balance_factor > 1 && get_balance_factor(node->left_side) < 0) {
		node->left_side =  rotate_left(node->left_side);
		return rotate_right(node);
	}

	if (balance_factor < -1 && get_balance_factor(node->right_side) > 0) {
		node->right_side = rotate_right(node->right_side);
		return rotate_left(node);
	}

	return node;
}

int count_number_of_nodes(const struct avl_tree *node) {
	if (node == NULL) {
		return 0;
	}

	return 1 + count_number_of_nodes(node->left_side) + count_number_of_nodes(node->right_side);
}

void pre_order_tree(const struct avl_tree *node) {
	if (node != NULL) {
		char left_side = node->left_side != NULL ? node->left_side->node_id : PLACEHOLDER;
		char right_side = node->right_side != NULL ? node->right_side->node_id : PLACEHOLDER;

		printf(
			"current: %c\nheight: %d\nleft: %c\nright: %c\n%s\n",
			node->node_id, node->height, left_side, right_side, SEPARATOR
		);
		pre_order_tree(node->left_side);
		pre_order_tree(node->right_side);
	}
}

void in_order_tree(const struct avl_tree *node) {
	if (node != NULL) {
		char left_side = node->left_side != NULL ? node->left_side->node_id : PLACEHOLDER;
		char right_side = node->right_side != NULL ? node->right_side->node_id : PLACEHOLDER;

		in_order_tree(node->left_side);
		printf(
			"current: %c\nheight: %d\nleft: %c\nright: %c\n%s\n",
			node->node_id, node->height, left_side, right_side, SEPARATOR
		);
		in_order_tree(node->right_side);
	}
}

void post_order_tree(const struct avl_tree *node) {
	if (node != NULL) {
		char left_side = node->left_side != NULL ? node->left_side->node_id : PLACEHOLDER;
		char right_side = node->right_side != NULL ? node->right_side->node_id : PLACEHOLDER;

		post_order_tree(node->left_side);
		post_order_tree(node->right_side);
		printf(
			"current: %c\nheight: %d\nleft: %c\nright: %c\n%s\n",
			node->node_id, node->height, left_side, right_side, SEPARATOR
		);
	}
}

void remove_full_avl_tree(struct avl_tree *node) {
	if (node != NULL) {
		remove_full_avl_tree(node->left_side);
		remove_full_avl_tree(node->right_side);
		free(node);
	}
}

void print_separator(const char *message) {
	printf("%s\n%s\n%s\n", SEPARATOR, message, SEPARATOR);
}

bool on_node_exists(struct avl_tree *node, const char node_id) {
	struct avl_tree *current = node;

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

struct avl_tree *rotate_right(struct avl_tree *node) {
	if (node == NULL) {
		return NULL;
	}

	struct avl_tree *left = node->left_side;
	struct avl_tree *temp = left->right_side;

	left->right_side = node;
	node->left_side = temp;
	node->height = MAX_VALUE(get_tree_height(node->left_side), get_tree_height(node->right_side)) + 1;
	left->height = MAX_VALUE(get_tree_height(left->left_side), get_tree_height(left->right_side)) + 1;

	return left;
}

struct avl_tree *rotate_left(struct avl_tree *node) {
	if (node == NULL) {
		return NULL;
	}

	struct avl_tree *right = node->right_side;
	struct avl_tree *temp = right->left_side;

	right->left_side = node;
	node->right_side = temp;
	node->height = MAX_VALUE(get_tree_height(node->left_side), get_tree_height(node->right_side)) + 1;
	right->height = MAX_VALUE(get_tree_height(right->left_side), get_tree_height(right->right_side)) + 1;

	return right;
}

int get_tree_height(struct avl_tree *node) {
	if (node == NULL) {
		return 0;
	}

	return node->height;
}

int get_balance_factor(struct avl_tree *node) {
	if (node == NULL) {
		return 0;
	}

	return get_tree_height(node->left_side) - get_tree_height(node->right_side);
}