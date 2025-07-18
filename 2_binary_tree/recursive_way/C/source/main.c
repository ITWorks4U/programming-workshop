/*
* Simple binary tree example by using C language.
*
* author:	ITWorks4U
* created:	July 15th, 2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/binary_tree.h"

int main(void) {
	char word[] = "ITWorks4U";

	/*	inserting	*/
	print_separator("Inserting...");
	struct binary_tree *tree = NULL;

	for(size_t i = 0; i < strlen(word); i++) {
		tree = insert_into_tree(tree, word[i]);
	}

	/*	PRE-ORDER, IN-ORDER, POST-ORDER	*/
	print_separator("PRE-ORDER:");
	pre_order_tree(tree);

	print_separator("IN-ORDER:");
	in_order_tree(tree);

	print_separator("POST-ORDER:");
	post_order_tree(tree);

	/*	deleting a node	*/
	print_separator("deleting a node");
	printf("Enter a node ID to delete, if exists: ");

	/*
	* just reading only one character from stdin, whereas
	* the remaining buffer needs to be flushed from memory
	*/
	char c = getchar();
	int remaining_chars;
	while ((remaining_chars = getchar() != '\n' && remaining_chars != EOF));

	if (!on_node_exists(tree, c)) {
		fprintf(stderr, "ERROR: The current node \"%c\" was not found in the binary tree.\n", c);
	} else {
		tree = delete_node(tree, c);

		/*	print it out again	*/
		print_separator("updated tree:");
		pre_order_tree(tree);
	}

	/*	appending a new node into the binary tree, because... Why not?	*/
	print_separator("appending new node");
	printf("Add a new node to the binary tree: ");
	c = getchar();
	while ((remaining_chars = getchar() != '\n' && remaining_chars != EOF));
	if ((tree = insert_into_tree(tree, c)) == NULL) {
		fprintf(stderr, "ERROR: A node with the ID \"%c\" already exists in the current binary tree.\n", c);
	} else {
		/*	print it out again	*/
		print_separator("updated tree:");
		pre_order_tree(tree);
	}

	/*	delete the full binary tree	*/
	print_separator("delete full tree");
	remove_full_binary_tree(tree);
	tree = NULL;
	printf("tree is NULL...? %s\n", tree == NULL ? "yes" : "no");

	return EXIT_SUCCESS;
}