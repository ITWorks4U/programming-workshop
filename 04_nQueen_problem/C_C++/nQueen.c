#include "nQueen.h"
#include <stdio.h>
#include <stdlib.h>

bool on_safe_field(char **board, int row, int column, int number_of_fields) {
	int i,j;

	for (i = 0; i < column; i++) {													/*	check this row on the left side	*/
		if (board[row][i] == 'Q') {
			return false;
		}
	}

	for (i = row, j = column; i >= 0 && j >= 0; i--, j--) {							/*	check upper diagonal on left side	*/
		if (board[i][j] == 'Q') {
			return false;
		}
	}

	for (i = row, j = column; j >= 0 && i < number_of_fields; i++, j--) {			/*	check lower diagonal on left side	*/
		if (board[i][j] == 'Q') {
			return false;
		}
	}

	return true;
}

bool solve_queen_problem(char **board, int column, int number_of_fields) {
	if (column >= number_of_fields) {
		return true;
	}

	int i;
	for (i = 0; i < number_of_fields; i++) {
		if (on_safe_field(board, i, column, number_of_fields)) {					/*	check, if queen q can be placed on the board {i,column}	*/
			board[i][column] = 'Q';													/*	place this queen q on board {i,column}	*/

			if (solve_queen_problem(board, column + 1, number_of_fields)) {			/*	recur to place rest of the queens	*/
				return true;
			}

			board[i][column] = '-';													/*	backtracking: placing of queen q didn't match	*/
		}
	}

	return false;																	/*	the queen q can't be placed in any row or column	*/
}

void print_solution(char **board, int number_of_fields) {
	int i,j;

	for (i = 0; i < number_of_fields; i++) {
		for (j = 0; j < number_of_fields; j++) {
			printf(" %c", board[i][j]);
		}

		printf("\n");
	}
}

void init_queen_problem(int number_of_fields) {
	char **board = create_field(number_of_fields);

	if (board != NULL) {
		if (!(solve_queen_problem(board, 0, number_of_fields))) {
			puts(".:no solution found:.");
		} else {
			print_solution(board, number_of_fields);
		}

		clean_up(board, number_of_fields);
	} else {
		fprintf(stderr, "Creation of field with %d fields were impossible.\n", number_of_fields);
	}
}

void clean_up(char **field_to_remove, int number_of_fields) {
	int i;
	for (i = 0; i < number_of_fields; i++) {
		free(field_to_remove[i]);
	}

	free(field_to_remove);
}

char **create_field(int number_of_fields) {
	char **field = NULL;
	field = (char **) calloc(number_of_fields, sizeof(char *));

	if (field == NULL) {
		clean_up(field, number_of_fields);
	} else {
		int i, j;

		for (i = 0; i < number_of_fields; i++) {
			field[i] = (char *) calloc(number_of_fields, sizeof(char));
			
			if (field[i] == NULL) {
				free(field[i]);
				return NULL;
			}
		}

		for (i = 0; i < number_of_fields; i++) {
			for(j = 0; j < number_of_fields; j++) {
				field[i][j] = '-';
			}
		}
	}

	return field;
}