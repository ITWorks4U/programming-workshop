SOURCE = source/n_queen_problem.c source/main.c
TARGET = n_queen_problem.run
FLAGS = -g3 -Wall -Iinclude
COMPILER = gcc

all:
		@$(COMPILER) $(FLAGS) $(SOURCE) -o $(TARGET)
		$(info Application has been built.)

clean:
		@rm -f $(TARGET)
		$(info Application has been removed.)