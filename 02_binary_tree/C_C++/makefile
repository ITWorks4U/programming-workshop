all:					binaryTree.o binaryTreeRunner.o
						gcc -g3 -Wall -o binaryTreeRunner.run binaryTreeRunner.o binaryTree.o
						rm *.o

binaryTree.o:			binaryTree.c binaryTree.h
						gcc -c -g3 -Wall binaryTree.c

binaryTreeRunner.o:		binaryTreeRunner.c binaryTree.h
						gcc -c -g3 -Wall binaryTreeRunner.c

clean:
						rm binaryTreeRunner.run