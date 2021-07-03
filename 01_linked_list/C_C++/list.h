#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#define LENGTH	32

struct LinkedList {
	int node_id;
	char data[LENGTH];

	struct LinkedList *next;
};

void print_list(void);
void add_to_list(char content[]);
void remove_from_list(int remove_key);
void reverse_list(void);
void clear_list(void);

#endif