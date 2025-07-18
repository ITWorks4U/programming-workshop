/*
* Simple binary tree example by using C language.
*
* author:	ITWorks4U
* created:	July 15th, 2025
*/

#ifndef	BINARY_TREE_H
#define	BINARY_TREE_H

#include <stdbool.h>

/*	definition(s)	*/
#define	UNDEFINED_NODE	'\0'
#define	PLACEHOLDER		' '
#define	TREE_NOT_EXIST	"no binary tree exists yet"
#define	SEPARATOR		"------------"

/*	structure(s)	*/
struct binary_tree {
	/*	ID to store for the current node	*/
	char node_id;

	/*	left side of this node	*/
	struct binary_tree *left_side;

	/*	right side of this node	*/
	struct binary_tree *right_side;
};

/*	function(s)		*/

/// @brief Inserting a new element to the binary tree by using recursion.
/// This binary tree still not allows to handle duplicates.
/// @param node the current node to handle
/// @param node_id the ID to insert into the binary tree
/// @return the next binary tree reference
struct binary_tree *insert_into_tree(struct binary_tree *node, const char node_id);

/// @brief Returning the minimal value from the binary tree.
/// @return the minimal value from the binary tree
struct binary_tree *get_minimal_node_value(struct binary_tree *node);

/// @brief Remove the current node from the binary tree.
/// @param node the current node to handle
/// @param node_id the ID to look for
/// @return the reference to the next and previous node
struct binary_tree *delete_node(struct binary_tree *node, const char node_id);

/// @brief Counting the number of nodes of the current binary tree.
/// More in use for deleting the full binary tree.
/// @param node current node with possible child(s)
/// @return 0, if this node is NULL,
/// 1 + the number of left and right childs
int count_number_of_nodes(const struct binary_tree *node);

/// @brief Remove the full binary tree.
/// @param node node, which may have childs
void remove_full_binary_tree(struct binary_tree *node);

/// @brief Displaying the binary tree in PRE-ORDER.
/// Starting with the node, followed by the left side and finally
/// the right side of the current node.
/// @param node node to use
void pre_order_tree(const struct binary_tree *node);

/// @brief Displaying the binary tree in IN-ORDER.
/// Starting with the left side, followed by the current node and
/// finally the right side of the node.
/// @param node node to use
void in_order_tree(const struct binary_tree *node);

/// @brief Displaying the binary tree in POST-ORDER.
///	Starting with the left side, followed by the right side and
/// finally the current node itself.
/// @param node note to use
void post_order_tree(const struct binary_tree *node);

/// @brief Print a separator block to the terminal.
/// @param message the message within the block
void print_separator(const char *message);

/// @brief Checks, if the node exists
/// @param node_id ID to look for
/// @return true, if the node exists, otherwise false
bool on_node_exists(struct binary_tree *node, const char node_id);
#endif