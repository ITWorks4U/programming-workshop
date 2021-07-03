#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main(void) {
	char buffer[LENGTH] = {'\0'};
	const char END_WORD[] = "#END";

	printf(" *** to stop to add a new element, type %s\n", END_WORD);

	do {
		printf(" add content: ");
		fgets(buffer, LENGTH, stdin);

		fflush(stdin);

		size_t contentSize = strlen(buffer);
		buffer[contentSize - 1] = '\0';

		add_to_list(buffer);

	} while (strcmp(buffer, END_WORD) != 0);
	
	printf("\n");
	print_list();

	//--------------------------------------
	printf(" Removing node with ID: ");
	fgets(buffer, LENGTH, stdin);

	int nodeID = strtol(buffer, NULL, 10);
	remove_from_list(nodeID);
	print_list();
	//--------------------------------------

	puts("\nreversing list:");
	reverse_list();
	print_list();

	//--------------------------------------
	clear_list();

	return EXIT_SUCCESS;
}