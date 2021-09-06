all:				server.o client.o logger.o
					gcc -g3 -Wall -pthread -o server.run server.o logger.o
					gcc -g3 -Wall -pthread -o client.run client.o logger.o
					rm *.o

server_only:		server.o logger.o
					gcc -g3 -Wall -pthread -o server.run server.o logger.o
					rm *.o

client_only:		client.o logger.o
					gcc -g3 -Wall -pthread -o client.run client.o logger.o
					rm *.o

server.o:			server.c chat.h logger.h server.h
					gcc -g3 -Wall -c server.c

client.o:			client.c chat.h logger.h client.h
					gcc -g3 -Wall -c client.c

logger.o:			logger.c chat.h logger.h
					gcc -g3 -Wall -c logger.c

clean:
					rm server.run
					rm client.run