all:					avl_tree.o avl_tree_runner.o
						gcc -g3 -Wall -o avl_tree.run avl_tree_runner.o avl_tree.o
						rm *.o

avl_tree.o:				avl_tree.c avl_tree.h
						gcc -c -g3 -Wall avl_tree.c

avl_tree_runner.o:		avl_tree_runner.c avl_tree.h
						gcc -c -g3 -Wall avl_tree_runner.c

clean:
						rm avl_tree.run