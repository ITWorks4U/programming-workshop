/*
* Simple linked list example by using C language.
*
* author:	ITWorks4U
* created:	July 14th, 2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/linked_list.h"

int main(void) {
	char buffer[BUFFER_LENGTH];
	printf("enter %s to stop adding elements to the linked list...\n", END_OF_INPUT);

	do {
		reset_input_buffer(buffer);
		fgets(buffer, BUFFER_LENGTH, stdin);
		check_for_newline(buffer);

		//	even buffer contains "nothing" or just "q" (for quit) this is a valid input
		add_to_list(buffer);
	} while(strcmp(buffer, END_OF_INPUT) != 0);

	//	------
	//	printing the full list
	//	------
	print_separator("printing full list");
	print_list();

	//	------
	//	looking for ID
	//	------
	print_separator("looking for ID in list");
	int resulting_id;

	reset_input_buffer(buffer);
	printf("enter ID to look for: ");
	fgets(buffer, BUFFER_LENGTH, stdin);
	check_for_newline(buffer);

	if (!on_valid_input(buffer)) {
		fprintf(stderr, "(SEARCH) invalid input: %s\n", buffer);
	} else {
		resulting_id = (int)strtol(buffer, NULL, 10);

		if (on_existing_node(resulting_id)) {
			printf("content for id %d: %s\n", resulting_id, get_content_from_list(resulting_id));
		} else {
			printf("ID %d not found in list...\n", resulting_id);
		}
	}

	//	------
	//	removing node
	//	------
	print_separator("removing from list");
	reset_input_buffer(buffer);
	printf("enter ID to remove from list: ");
	fgets(buffer, BUFFER_LENGTH, stdin);
	check_for_newline(buffer);

	if (!on_valid_input(buffer)) {
		fprintf(stderr, "(REMOVE) invalid input: %s\n", buffer);
	} else {
		resulting_id = (int)strtol(buffer, NULL, 10);
		remove_from_list(resulting_id);
	}

	//	------
	//	reversing list
	//	------
	print_separator("reversing list");
	reverse_list();
	print_list();

	//	------
	//	clean up
	//	------
	print_separator("clean up the mess");
	clean_up();

	return EXIT_SUCCESS;
}