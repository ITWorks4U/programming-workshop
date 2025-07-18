/*
* Simple linked list example by using C language.
*
* author:	ITWorks4U
* created:	July 14th, 2025
* updated:	July 16th, 2025
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/double_linked_list.h"

static struct linked_list *root = NULL;

void print_list(void) {
	int nbr_of_elements = 0;
	struct linked_list *current = root;

	while(current != NULL) {
		printf(
			"ID: %d\ncontent: %s\nprevious node ID: %d\nnext node ID: %d\n\n",
			current->node_id, current->content,
			current->prev != NULL ? current->prev->node_id : INVALID_NODE_ID,
			current->next != NULL ? current->next->node_id : INVALID_NODE_ID
		);
		current = current->next;
		nbr_of_elements++;
	}

	printf("\n> total umber of nodes: %d\n", nbr_of_elements);
}

void add_to_list(const char *new_content) {
	if (root == NULL) {
		root = (struct linked_list*) calloc(1, sizeof(struct linked_list));

		if (on_valid_content_length(new_content)) {
			strcpy(root->content, new_content);
		} else {
			strcpy(root->content, INVALID_CONTENT);
			fprintf(stderr, "%s\n", INVALID_CONTENT);
		}
	} else {
		struct linked_list *current = root;

		while(current->next != NULL) {
			current = current->next;
		}

		struct linked_list *new_node = (struct linked_list*) calloc(1, sizeof(struct linked_list));
		new_node->node_id = current->node_id + 1;
		new_node->prev = current;

		if (on_valid_content_length(new_content)) {
			strcpy(new_node->content, new_content);
		} else {
			strcpy(new_node->content, INVALID_CONTENT);
			fprintf(stderr, "%s\n", INVALID_CONTENT);
		}

		current->next = new_node;
	}
}

void remove_from_list(int id_to_remove) {
	if (root == NULL) {
		fprintf(stderr, "%s\n", LIST_IS_EMPTY);
		return;
	}

	if (!on_existing_node(id_to_remove)) {
		fprintf(stderr, "%s\n", NODE_NOT_EXISTS);
		return;
	}

	struct linked_list *current = root;

	while(current != NULL) {
		if (current->node_id == id_to_remove) {
			/*	removing root, if needed	*/
			if (current == root) {
				root = current->next;		//	move root to the next pointer address

				if (root != NULL) {
					root->prev = NULL;		//	set the previous pointer to NULL
				}
			} else {
				/*	updating the neighbour's links	*/
				if (current->prev != NULL) {
					current->prev->next = current->next;
				}

				if (current->next != NULL) {
					current->next->prev = current->prev;
				}
			}

			free(current);
			printf("removed element id: %d from list...\n", id_to_remove);
			return;
		}

		current = current->next;
	}
}

void reverse_list(void) {
	struct linked_list *tmp = NULL;
	struct linked_list *current = root;

	while (current != NULL) {
		/*	swapping prev and next	*/
		tmp = current->prev;
		current->prev = current->next;
		current->next = tmp;

		/*	move to the next node in the original sequence	*/
		current = current->prev;
	}

	/*	finally, update root as well	*/
	if (tmp != NULL) {
		root = tmp->prev;
	}
}

void clean_up(void) {
	struct linked_list *current = root;
	struct linked_list *temp = NULL;

	while(current != NULL) {
		temp = current->next;
		free(current);
		current = temp;
	}

	root = NULL;
}

bool on_valid_content_length(const char *content_to_insert) {
	return strlen(content_to_insert) < BUFFER_LENGTH;
}

bool on_existing_node(int id_to_look_for) {
	struct linked_list *current = root;

	while(current != NULL) {
		if (current->node_id == id_to_look_for) {
			return true;
		}

		current = current->next;
	}

	return false;
}

char *get_content_from_list(int id_to_look_for) {
	if (root == NULL) {
		fprintf(stderr, "%s\n", LIST_IS_EMPTY);
		return NULL;
	}

	struct linked_list *current = root;

	while(current != NULL) {
		if (current->node_id == id_to_look_for) {
			return current->content;
		}

		current = current->next;
	}

	fprintf(stderr, "%s\n", NODE_NOT_EXISTS);
	return NULL;
}

void reset_input_buffer(char *buffer) {
	memset(buffer, '\0', BUFFER_LENGTH);
}

void check_for_newline(char *buffer) {
	size_t length = strlen(buffer);

	if (length > 0 && buffer[length-1] == '\n') {
		buffer[length-1] = '\0';
	}
}

void print_separator(const char *message) {
	puts("-------------------");
	printf("%s\n", message);
	puts("-------------------");
}

bool on_valid_input(const char *input) {
	int result = -1;

	#if POSIX_REGEX_AVAILABLE
	/*	using POSIX regex.h	*/
	regex_t reg;

	if (regcomp(&reg, REGEX_PATTERN, REG_EXTENDED) < 0) {
		return false;
	}

	result = regexec(&reg, input, 0, NULL, 0);
	regfree(&reg);

	#elif REGEX_C_WINDOWS
	/*	using PCRE2 instead	*/

	PCRE2_SIZE erroffset;
	int errorcode = -1;

	PCRE2_SPTR pattern = (PCRE2_SPTR)REGEX_PATTERN;
	PCRE2_SPTR subject = (PCRE2_SPTR)input;

	pcre2_code *re = pcre2_compile(
		pattern,               // the pattern
		PCRE2_ZERO_TERMINATED, // indicates pattern is zero-terminated
		0,                     // default options
		&errorcode,            // for error code
		&erroffset,            // for error offset
		NULL);                 // use default compile context

	if (re == NULL) {
		fprintf(stderr, "PCRE2 compilation failed at offset %d\n", (int)erroffset);
		return false;
	}

	pcre2_match_data *match_data = pcre2_match_data_create_from_pattern(re, NULL);
	result = pcre2_match(re, subject, strlen((char *)subject), 0, 0, match_data, NULL);

	pcre2_match_data_free(match_data);
	pcre2_code_free(re);

	#else
	/*	otherwise no regular expression is able to do here	*/
	return result == 0;
	#endif
}