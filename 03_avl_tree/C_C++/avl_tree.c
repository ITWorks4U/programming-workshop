#include<stdio.h>
#include<stdlib.h>
#include "avl_tree.h"

int get_tree_height(struct Node *node) {
	if (node == NULL) {
		return 0;
	}

	return node->height;
}

int get_max_value(int a, int b) {
	if (a > b) {
		return a;
	}

	return b;
}

int get_balance_factor(struct Node *node) {
	if (node == NULL) {
		return 0;
	}

	return (get_tree_height(node->left) - get_tree_height(node->right));
}

struct Node *rotate_right(struct Node *node) {
	struct Node *left_side = node->left;
	struct Node *tmp = left_side->right;

	left_side->right = node;
	node->left = tmp;

	node->height = get_max_value(get_tree_height(node->left), get_tree_height(node->right))+1;
	left_side->height = get_max_value(get_tree_height(left_side->left), get_tree_height(left_side->right))+1;

	return left_side;
}

struct Node *rotate_left(struct Node *node) {
	struct Node *right_side = node->right;
	struct Node *tmp = right_side->left;

	right_side->left = node;
	node->right = tmp;

	node->height = get_max_value(get_tree_height(node->left), get_tree_height(node->right))+1;
	right_side->height = get_max_value(get_tree_height(right_side->left), get_tree_height(right_side->right))+1;

	return right_side;
}

struct Node* new_node(char data) {
	struct Node* node = (struct Node*) malloc(sizeof(struct Node));
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	
	return node;
}

struct Node* insert(struct Node* node, char data) {
	if (node == NULL) {
		return new_node(data);
	}

	if (data < node->data) {
		node->left = insert(node->left, data);
	} else if (data > node->data) {
		node->right = insert(node->right, data);
	} else {
		return node;
	}

	node->height = 1 + get_max_value(get_tree_height(node->left), get_tree_height(node->right));
	int balance = get_balance_factor(node);

	if (balance > 1 && data < node->left->data) {
		return rotate_right(node);
	}

	if (balance < -1 && data > node->right->data) {
		return rotate_left(node);
	}

	if (balance > 1 && data > node->left->data) {
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	if (balance < -1 && data < node->right->data) {
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}

	return node;
}

struct Node * min_node_value(struct Node* node) { 
	struct Node* current = node;

	while (current->left != NULL) {
		current = current->left;
	}

	return current; 
}
 
struct Node* delete_node(struct Node* root, char key) {
	if (root == NULL) { 
		return NULL;
	}

	if (key < root->data) { 
		root->left = delete_node(root->left, key);
	} else if( key > root->data ) { 
		root->right = delete_node(root->right, key);
	} else {
		if((root->left == NULL) || (root->right == NULL)) {
			struct Node *temp = root->left ? root->left : root->right; 

			if (temp == NULL) { 
				temp = root;
				root = NULL;
			} else {
				*root = *temp;
			}

			free(temp); 
		} else {
			struct Node* temp = min_node_value(root->right);
			root->data = temp->data;
			root->right = delete_node(root->right, temp->data); 
		}
	}

	if (root == NULL) {
		return NULL;
	}

	root->height = 1 + get_max_value(get_tree_height(root->left), get_tree_height(root->right));
	int balance = get_balance_factor(root); 

	if (balance > 1 && get_balance_factor(root->left) >= 0) {
		return rotate_right(root);
	}

	if (balance > 1 && get_balance_factor(root->left) < 0) {
		root->left =  rotate_left(root->left);
		return rotate_right(root);
	}

	if (balance < -1 && get_balance_factor(root->right) <= 0) {
		return rotate_left(root);
	}

	if (balance < -1 && get_balance_factor(root->right) > 0) {
		root->right = rotate_right(root->right);
		return rotate_left(root);
	}

	return root;
}

void pre_order(struct Node *root) {
	if(root != NULL) {
		printf("data: %c, height: %d\n", root->data, root->height);
		pre_order(root->left);
		pre_order(root->right);
	}
}

void in_order(struct Node *root) {
	if (root != NULL) {
		in_order(root->left);
		printf("data: %c, height: %d\n", root->data, root->height);
		in_order(root->right);
	}
}

void post_order(struct Node *root) {
	if (root != NULL) {
		post_order(root->left);
		post_order(root->right);
		printf("data: %c, height: %d\n", root->data, root->height);
	}
}

void clear_tree(struct Node *node) {
	if (node != NULL) {
		clear_tree(node->left);
		clear_tree(node->right);
		free(node);
	}
}