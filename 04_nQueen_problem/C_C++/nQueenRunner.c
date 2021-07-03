#include "nQueen.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {

	int i;
	for (i = 1; i <= 20; i++) {
		if (i == 1) {
			printf("using %d field...\n\n", i);
		} else {
			printf("using %d fields...\n\n", i);
		}

		init_queen_problem(i);
		puts("\n----------");
	}

	return EXIT_SUCCESS;
}