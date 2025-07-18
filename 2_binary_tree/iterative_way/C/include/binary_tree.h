/*
* Simple binary tree example by using C language.
*
* author:	ITWorks4U
* created:	July 14th, 2025
* updated:	July 16th, 2025
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

/// @brief Returning the root of the binary tree.
/// @return the root of the binary tree
struct binary_tree *get_root(void);

/// @brief Create a new node for the binary tree.
/// @param node_id ID for the new node
/// @return the new created node (pointer) for the binary tree
struct binary_tree *create_new_node(const char node_id);

/// @brief Inserting a new node to the binary tree. In combination with
/// create_new_node(node_id) function the new node is going to append to
/// the binary tree.
/// @param node_id ID for the new node
/// @return true, on success, otherwise false
bool insert_into_tree(const char node_id);

/// @brief Returning the minimal value from the binary tree.
/// @return the minimal value from the binary tree
char get_minimal_node_value(void);

/// @brief Remove the node from the binary tree. There're three cases to handle:
/// case 1: node has left and right child
/// case 2: node has one child (either left or right)
/// case 3: node has no childs (node is a leaf)
/// @param node_id ID to look for
/// @return true, if the node has been removed,
/// false, if root is NULL or the ID was not found
bool delete_node(const char node_id);

/// @brief Counting the number of nodes of the current binary tree.
/// More in use for deleting the full binary tree.
/// @param node current node with possible child(s)
/// @return 0, if this node is NULL,
/// 1 + the number of left and right childs
int count_number_of_nodes(const struct binary_tree *node);

/// @brief Removing the full binary tree.
void remove_full_binary_tree(void);

/// @brief Also removing the full binary tree. In contrast to
/// remove_full_binary_tree, this function cooperates with
/// delete_node() function, however, this might cause a more
/// higher time amount depending on the size of the binary tree.
void remove_full_binary_tree_alternative(void);

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
bool on_node_exists(const char node_id);
#endif