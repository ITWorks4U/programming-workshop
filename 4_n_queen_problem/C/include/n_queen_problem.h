/*
* Solving the n queen problem in C for a dynamically field
* in the range of 1x1 to 16x16.
*
* author:		ITWorks4U
* created:		July 17th, 2025
* updated:		July 22nd, 2025
*/

#ifndef N_QUEEN_PROBLEM
#define N_QUEEN_PROBLEM

#include <stdbool.h>

/*	definition(s)	*/
#define UPPER_BOUNDARY	20
#define QUEEN_FIGURE	'Q'
#define NO_FIGURE		'-'
#define START_FIELD		0
#define SEPARATOR		"--------------"

/*	external definition(s)	*/
/// @brief The chess board to use.
extern char **chess_board;

/// @brief The number of fields to use for the certain chessboard
/// in the range of 1x1 to 20x20. 
extern int number_of_fields;

/*	function(s)	*/

/// @brief Check, if the field, where a Queen is going to place is save. This field is
/// save only, if no other queen covers this field in horizontal, vertical or diagonal way.
/// @param row current row
/// @param column current column
/// @return true, if the queen can be placed in that certain field,
/// false, otherwise
bool on_safe_field(int row, int column);

/// @brief Try to solve the n queen problem by using a chess board in the range of 1x1 to 20x20.
/// @param column the column to start
/// @return true, if the n queen problem was able to solve
/// false, otherwise
bool try_to_solve(int column);

/// @brief Print the current solution to stdout.
void print_solution(void);

/// @brief Initializing a new chess board.
/// @param number_of_fields the number of fields to use
/// @return true, if the current n queen problem was solved
/// false, otherwise
bool run_queen_problem(int number_of_fields);

/// @brief Clean up the mess.
void clean_up();

/// @brief Create a dynamically chess board depending on the number of fields.
/// @param number_of_fields the number of fields to use
/// @return the chess board for the current simulation
char **create_field(int number_of_fields);

/// @brief Print a title for a clean overview.
/// @param message message to display on stdout
void print_title(const char *message);
#endif