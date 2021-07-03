#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"

int main() {
	struct Node *root = NULL;

	char elements[] = {'I','T','W','o','r','k','s','4','U'};
	size_t arr_length = sizeof(elements) / sizeof(elements[0]);
	int i;

	for(i = 0; i < arr_length; i++) {
		root = insert(root, elements[i]);
	}

	puts("\npre-order:"); 
	pre_order(root);

	puts("\nin-order:");
	in_order(root);

	puts("\npost-order:");
	post_order(root); 

	root = delete_node(root, 'W');

	printf("\nPreorder traversal after deletion of W \n"); 
	pre_order(root);
	printf("\n");

	clear_tree(root);

	return EXIT_SUCCESS;
}