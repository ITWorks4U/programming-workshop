all:				list.o listRunner.o
					gcc -g3 -Wall -o linkedList.run list.o listRunner.o
					rm *.o

list.o:				list.c list.h
					gcc -c -Wall list.c

listRunner.o:		listRunner.c list.h
					gcc -c -Wall listRunner.c

clean:
					rm linkedList.run