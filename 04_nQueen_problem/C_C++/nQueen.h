#pragma once
#include <stdbool.h>

bool on_safe_field(char **board, int row, int column, int number_of_fields);
bool solve_queen_problem(char **board, int column, int number_of_fields);

void print_solution(char **board, int number_of_fields);
void init_queen_problem(int number_of_fields);
void clean_up(char **field_to_remove, int number_of_fields);

char **create_field(int number_of_fields);
