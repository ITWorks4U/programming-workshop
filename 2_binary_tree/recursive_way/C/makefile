SOURCE = source/binary_tree.c source/main.c
TARGET = binary_tree.run
FLAGS = -g3 -Wall -Iinclude
COMPILER = gcc

all:
		@$(COMPILER) $(FLAGS) $(SOURCE) -o $(TARGET)
		$(info Application has been built.)

clean:
		@rm -f $(TARGET)
		$(info Application has been removed.)