/*
* Using an AVL tree in C language.
*
* author:	ITWorks4U
* created:	July 16th, 2025
*/

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdbool.h>

/*	definition(s)	*/
#define	UNDEFINED_NODE	'\0'
#define	PLACEHOLDER		' '
#define	TREE_NOT_EXIST	"no AVL tree exists yet"
#define	SEPARATOR		"------------"

/*	determine the maximum value of two given values	*/
#define	MAX_VALUE(a,b) ((a) < (b) ? (b) : (a))

/*	structure(s)	*/
struct avl_tree {
	/*	node identification	*/
	char node_id;

	/*	left side of the AVL tree	*/
	struct avl_tree *left_side;

	/*	right side of the AVL tree	*/
	struct avl_tree *right_side;

	/*	the actual height of the tree	*/
	int height;
};

/*	function(s)		*/

/// @brief Insert a new node into the AVL tree. If the tree is not in balance,
/// a rotation to the left or right is on the way. This AVL tree does not support
/// multiple nodes.
/// @param node current node to handle
/// @param node_id ID to insert into the tree
/// @return 
struct avl_tree* insert_into_avl_tree(struct avl_tree* node, const char node_id);

/// @brief Returning the minimal value from the AVL tree.
/// @return the minimal value from the binary tree 
struct avl_tree * get_minimal_node_value(struct avl_tree* node);

/// @brief Remove the current node from the AVL tree.
/// @param node the current node to handle
/// @param node_id the ID to look for
/// @return the reference to the next and previous node
struct avl_tree* delete_node(struct avl_tree* node, const char node_id);

/// @brief Counting the number of nodes of the current binary tree.
/// More in use for deleting the full binary tree.
/// @param node current node with possible child(s)
/// @return 0, if this node is NULL,
/// 1 + the number of left and right childs
int count_number_of_nodes(const struct avl_tree *node);

/// @brief Displaying the binary tree in PRE-ORDER.
/// Starting with the node, followed by the left side and finally
/// the right side of the current node.
/// @param node node to use
void pre_order_tree(const struct avl_tree *node);

/// @brief Displaying the binary tree in IN-ORDER.
/// Starting with the left side, followed by the current node and
/// finally the right side of the node.
/// @param node node to use
void in_order_tree(const struct avl_tree *node);

/// @brief Displaying the binary tree in POST-ORDER.
///	Starting with the left side, followed by the right side and
/// finally the current node itself.
/// @param node note to use
void post_order_tree(const struct avl_tree *node);

/// @brief Remove the full AVL tree.
/// @param node node, which may have childs
void remove_full_avl_tree(struct avl_tree *node);

/// @brief Print a separator block to the terminal.
/// @param message the message within the block
void print_separator(const char *message);

/// @brief Checks, if the node exists
/// @param node_id ID to look for
/// @return true, if the node exists, otherwise false
bool on_node_exists(struct avl_tree *node, const char node_id);

/*	special functions for an AVL tree	*/

/// @brief Rotate the AVL tree to the right, when the left side dominates.
/// @param node the affected node
/// @return a balanced sub AVL tree in balance
struct avl_tree *rotate_right(struct avl_tree *node);

/// @brief Rotate the AVL tree to the left, when the right side dominates.
/// @param node the affected node
/// @return a balanced sub AVL tree in balance
struct avl_tree *rotate_left(struct avl_tree *node);

/// @brief Returning the current height of the AVL tree or the certain node.
/// @param node node to affect
/// @return the height of the AVL tree or node
int get_tree_height(struct avl_tree *node);

/// @brief Returning the balance factor of the AVL tree or the certain node.
/// If the balance factor exceeds 1, then a rotation to the left or right
/// is going to do.
/// @param node the affected node
/// @return the certain balance factor value
int get_balance_factor(struct avl_tree *node);
#endif