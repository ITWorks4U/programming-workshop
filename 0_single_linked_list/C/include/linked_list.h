/*
* Simple linked list example by using C language.
*
* author:	ITWorks4U
* created:	July 14th, 2025
* updated:	July 16th, 2025
*/

#ifndef LINKED_LIST_H
#define	LINKED_LIST_H

/*
*	If your system does not contain regex.h or supports an alternative way, like PCRE, to use
*	regular expressions in C only, there's no way to check against a valid user input.
*
*	By default a user input check against a valid number in the range [0-9]+ is in use
*	in this project.
*/
#if (__unix__ || __linux__) && __has_include(<regex.h>)
#include <regex.h>
#define	POSIX_REGEX_AVAILABLE	1
#elif _WIN32 && __has_include(<pcre2.h>)
#include <pcre2.h>
#define	REGEX_C_WINDOWS	1
#else
#warning "No POSIX regular expression libary has been found on your system."
#define	POSIX_REGEX_AVAILABLE	0
#endif

#include <stdbool.h>

/*	constant(s)		*/
#define	BUFFER_LENGTH	128
#define	INVALID_CONTENT	"***content length too large***"
#define	LIST_IS_EMPTY	"list is empty"
#define	NODE_NOT_EXISTS	"***node does not exist***"
#define	END_OF_INPUT	"q"
#define	INVALID_NODE_ID	-1

#if	POSIX_REGEX_AVAILABLE || REGEX_C_WINDOWS
#define	REGEX_PATTERN	"^[0-9]+$"
#endif

/*	structure(s)	*/
struct linked_list {
	/*	node ID	*/
	int node_id;

	/*	content for the certain node	*/
	char content[BUFFER_LENGTH];

	/*	link to the next node	*/
	struct linked_list *next;
};

/*	function(s)		*/

/// @brief Print all list nodes to the console.
void print_list(void);

/// @brief Add a new content to the newly created list node.
/// @param new_content content for newly created list node
void add_to_list(const char *new_content);

/// @brief Remove a node from list. If the list does not contain any data or
/// the ID is not found, a message is going to print to the console instead.
/// @param id_to_remove ID to remove from list
void remove_from_list(int id_to_remove);

/// @brief Reversing the full list.
void reverse_list(void);

/// @brief Removing all created list nodes from memory.
void clean_up(void);

/// @brief Checks, if the content to insert has a valid length. The length of
/// the C-string must not reach or exceed the defined length of 128 characters.
/// @param content_to_insert content to insert
/// @return true, if the content to insert does not reach or exceed the limitation area,
/// otherwise false
bool on_valid_content_length(const char *content_to_insert);

/// @brief Checks, if the requested node exists.
/// @param id_to_look_for ID to look for
/// @return true, if the node-id exists, otherwise false
bool on_existing_node(int id_to_look_for);

/// @brief Returning the content of the node by given ID.
/// If the list is empty or the certain ID was not found,
/// "NULL" returns.
/// @param id_to_look_for ID to look for
/// @return the content for node ID or NULL on mismatch
char *get_content_from_list(int id_to_look_for);

//	-------
//	for main() only
//	-------
/// @brief Clear the input buffer for next input sequence.
/// @param buffer buffer to reset
void reset_input_buffer(char *buffer);

/// @brief Check, if the input buffer contains '\n'. If true,
/// then this will be replaced with '\0'.
/// @param buffer buffer from input
void check_for_newline(char *buffer);

/// @brief Print a separator block to the terminal.
/// @param message the message within the block
void print_separator(const char *message);

/// @brief Checks, if the input is valid. The input is valid only,
/// if, and only if, a number or a sequence of numbers in the valid range
/// between [0,9] has been typed in. Any other characters, like non alpha numeric
/// characters, spaces, ... are not going to pass to the regular expression check.
///
///	ATTENTION:
///
///	This is only available, if POSIX regular expressions are able to handle on your system.
///	If not, then this function returns false by default.
/// @param input input to check for validity
/// @return true, if the input was valid, otherwise false, if the the regular expression
/// initializer has been failed or the input did not match or your system does not support
///	POSIX regular expressions
bool on_valid_input(const char *input);
#endif