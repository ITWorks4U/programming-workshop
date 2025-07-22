/*
* Solving the n queen problem in C for a dynamically field
* in the range of 1x1 to 20x20.
*
* author:		ITWorks4U
* created:		July 17th, 2025
* updated:		July 22nd, 2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/n_queen_problem.h"

#define BUFFER_HEADER	80

int main(void) {
	char header[BUFFER_HEADER];

	/*	create a list of solutions for each known NxN chess board	*/
	char *list_of_solutions[UPPER_BOUNDARY + 1];

	/*	initialize each sub field	*/
	for(int i = 0; i <= UPPER_BOUNDARY; i++) {
		list_of_solutions[i] = calloc(BUFFER_HEADER, sizeof(char));
	}

	for (int i = 1; i <= UPPER_BOUNDARY; i++) {
		memset(header, '\0', BUFFER_HEADER);
		sprintf(header, "Try to insert %d queen(s) into the chess board...\n", i);
		print_title(header);

		clock_t start = clock();
		bool on_solved = run_queen_problem(i);

		if (on_solved) {
			print_solution();
		}

		clean_up();
		clock_t end = clock();

		sprintf(
			list_of_solutions[i],
			"using %d queens: solution found: %s <=> measured time: %.4f seconds",
			i, on_solved ? "true" : "false", (double)(end-start) / CLOCKS_PER_SEC
		);
	}

	/*	print out each sub solution attempt	*/
	for(int i = 0; i <= UPPER_BOUNDARY; i++) {
		printf("%s\n", list_of_solutions[i]);
	}

	/*	clean up the mess	*/
	for(int i = 0; i <= UPPER_BOUNDARY; i++) {
		free(list_of_solutions[i]);
	}

	return EXIT_SUCCESS;
}