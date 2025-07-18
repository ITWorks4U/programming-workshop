/*
* Solving the n queen problem in C for a dynamically field
* in the range of 1x1 to 16x16.
*
* author:		ITWorks4U
* created:		July 17th, 2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/n_queen_problem.h"

#define BUFFER_HEADER	64

int main(void) {
	char header[BUFFER_HEADER];

	for (int i = 1; i <= UPPER_BOUNDARY; i++) {
		memset(header, '\0', BUFFER_HEADER);
		sprintf(header, "Try to insert %d queen(s) into the chess board...\n", i);
		print_title(header);

		if (run_queen_problem(i)) {
			print_solution();
		}

		clean_up();
	}

	return EXIT_SUCCESS;
}