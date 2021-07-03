all:			nQueen.o nQueenRunner.o
				gcc -g3 -Wall -o nQueen.run nQueen.o nQueenRunner.o
				rm *.o

nQueenRunner.o:	nQueenRunner.c nQueen.h
				gcc -c nQueenRunner.c

nQueen.o:		nQueen.c nQueen.h
				gcc -c nQueen.c

clean:
				rm nQueen.run