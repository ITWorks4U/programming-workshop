#ifndef TREE_H
#define TREE_H

struct Node {
	char data;
	struct Node *left;
	struct Node *right;

	int height;
};

struct Node* new_node(char data);
struct Node* insert(struct Node* node, char data);
struct Node * min_node_value(struct Node* node);
struct Node* delete_node(struct Node* root, char key);

void pre_order(struct Node *root);
void in_order(struct Node *root);
void post_order(struct Node *root);
void clear_tree(struct Node *node);

struct Node *rotate_right(struct Node *node);
struct Node *rotate_left(struct Node *node);
int get_max_value(int a, int b);
int get_tree_height(struct Node *node);
int get_balance_factor(struct Node *node);

#endif