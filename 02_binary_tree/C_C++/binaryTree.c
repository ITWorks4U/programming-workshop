// C program to insert a node in AVL tree
#include<stdio.h>
#include<stdlib.h>
#include "binaryTree.h"

// int get_max_value(int a, int b) {
// 	return 0;
// }

struct Node* new_node(char data) {
	struct Node *tmp = (struct Node *) malloc(sizeof(struct Node));

	tmp->left = NULL;
	tmp->right = NULL;
	tmp->data = data;

	return tmp;
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

	return node;
}

struct Node * min_node_value(struct Node* node) {
	struct Node *current = node;

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
		if ((root->left == NULL) || (root->right == NULL)) { 
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

	return root;
} 

void pre_order(struct Node *root) {
	if(root != NULL) {
		printf("data: %c\n", root->data);
		pre_order(root->left);
		pre_order(root->right);
	}
}

void in_order(struct Node *root) {
	if (root != NULL) {
		in_order(root->left);
		printf("data: %c\n", root->data);
		in_order(root->right);
	}
}

void post_order(struct Node *root) {
	if (root != NULL) {
		post_order(root->left);
		post_order(root->right);
		printf("data: %c\n", root->data);
	}
}

void clear_tree(struct Node *node) {
	if (node != NULL) {
		clear_tree(node->left);
		clear_tree(node->right);
		free(node);
	}
}