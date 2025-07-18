/*
* Solving the n queen problem in C for a dynamically field
* in the range of 1x1 to 16x16.
*
* author:		ITWorks4U
* created:		July 17th, 2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "..\include\n_queen_problem.h"

char **chess_board = NULL;
int number_of_fields = 1;

bool on_safe_field(int row, int column) {
	for(int i = 0; i < column; i++) {
		/*	check the current row, if there's a queen alreday placed	*/
		if (chess_board[row][i] == QUEEN_FIGURE) {
			return false;
		}
	}

	/*	check diagonal (top left to bottom right)	*/
	for(int i = row, j = column; i >= 0 && j >= 0; i--, j--) {
		if (chess_board[i][j] == QUEEN_FIGURE) {
			return false;
		}
	}

	/*	check diaginal (bottom left to top right)	*/
	for (int i = row, j = column; j >= 0 && i < number_of_fields; i++, j--) {
		if (chess_board[i][j] == QUEEN_FIGURE) {
			return false;
		}
	}

	return true;
}

bool try_to_solve(int column) {
	/*
	* If all queens has been successfully placed, then true will
	* return. Otherwise "no solution for any case" returns.
	*/
	if (column >= number_of_fields) {
		return true;
	}

	for (int i = 0; i < number_of_fields; i++) {
		/*	check, if queen q can be placed on the board {i,column}	*/
		if (on_safe_field(i, column)) {
			/*	place this queen q on board {i,column}	*/
			chess_board[i][column] = QUEEN_FIGURE;

			/*	try to place the next queen	*/
			if (try_to_solve(column + 1)) {
				return true;
			}

			/*	on this field can't be placed a queen	*/
			chess_board[i][column] = NO_FIGURE;
		}
	}

	return false;
}

void print_solution(void) {
	for(int i = 0; i < number_of_fields; i++) {
		for(int j = 0; j < number_of_fields; j++) {
			printf("%c ", chess_board[i][j]);
		}

		puts("");
	}
}

bool run_queen_problem(int number) {
	if (number < 1 || number > UPPER_BOUNDARY) {
		fprintf(stderr, "invalid number: %d\nthe number is in a range of [1,%d]\n", number, UPPER_BOUNDARY);
		return false;
	}

	number_of_fields = number;
	chess_board = create_field(number_of_fields);

	if (chess_board == NULL) {
		fprintf(stderr, "unable to create the board with %d fields...\n", number_of_fields);
		return false;
	}

	if (!try_to_solve(START_FIELD)) {
		fprintf(stderr, "No solution found for %d fields.\n", number_of_fields);
		return false;
	}

	return true;
}

void clean_up() {
	for(int i = 0; i < number_of_fields; i++) {
		free(chess_board[i]);
	}

	free(chess_board);
	chess_board = NULL;
}

char **create_field(int number_of_fields) {
	char **field = (char **) calloc(number_of_fields, sizeof(char *));

	if (field == NULL) {
		return NULL;
	}

	for (int i = 0; i < number_of_fields; i++) {
		field[i] = calloc(number_of_fields, sizeof(char));

		if (field[i] == NULL) {
			clean_up();
			return NULL;
		}

		/*	finally, set each field with '-' at the beginning	*/
		for(int j = 0; j < number_of_fields; j++) {
			field[i][j] = NO_FIGURE;
		}
	}

	return field;
}

void print_title(const char *message) {
	// Since in main() the current title comes with "\n"
	// there's no need to add an additional "\n" between
	// the two "%s" in the code.
	printf("\n%s\n%s%s\n", SEPARATOR, message, SEPARATOR);
}