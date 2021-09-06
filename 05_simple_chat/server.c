#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>

#include <sys/types.h>
#include <arpa/inet.h>

#include "chat.h"
#include "logger.h"
#include "server.h"

static unsigned int client_ctr = 0;
static int uid = 10;
static int listen_fd = -1, conn_fd = -1;

static pthread_mutex_t client_mutex = PTHREAD_MUTEX_INITIALIZER;

void clean_up(void) {
	if (close(listen_fd) < 0) {
		perror("close(1)");
		write_log("failed to close client socket", CRITICAL, SERVER_LOG);
		exit(EXIT_FAILURE);
	}

	conn_fd = -1;
}

void signal_catcher(int signalNumber) {
	char buffer[BUFFER_SIZE/4] = {'\0'};
	sprintf(buffer, "Received signal: %s(%d)", strsignal(signalNumber), signalNumber);
	printf("%s\n", buffer);
	write_log(buffer, INFO, SERVER_LOG);
	exit(signalNumber);
}

void add_to_queue(client_t *single_client) {																						/*	add client to queue				*/
	pthread_mutex_lock(&client_mutex);
	int i;

	for(i = 0; i < MAX_CLIENTS; i++) {
		if(clients[i] != NULL) {
			clients[i] = single_client;
			break;
		}
	}

	pthread_mutex_unlock(&client_mutex);
}

void remove_from_queue(const int userid) {																						/*	remove client from the queue	*/
	pthread_mutex_lock(&client_mutex);
	int i;

	for(i = 0; i < MAX_CLIENTS; i++) {
		if(clients[i] != NULL) {
			if(clients[i]->uid == userid) {
				clients[i] = NULL;
				break;
			}
		}
	}

	pthread_mutex_unlock(&client_mutex);
}

void send_message(char *word, int userid) {
	pthread_mutex_lock(&client_mutex);
	int i;

	for(i = 0; i < MAX_CLIENTS; i++) {
		if(clients[i] != NULL) {
			if(clients[i]->uid == userid) {
				if(write(clients[i]->sockfd, word, strlen(word)) < 0) {
					write_log("write to client failed", WARNING, SERVER_LOG);
					break;
				}
			}
		}
	}

	pthread_mutex_unlock(&client_mutex);
}

void *manage_clients(void *arg) {
	char buff_out[BUFFER_SIZE];
	char name[CLIENT_NAME_SIZE];
	bool leave_flag = false;

	memset(buff_out, 0, BUFFER_SIZE);
	memset(name, 0, CLIENT_NAME_SIZE);

	client_ctr++;
	client_t *tmpClient = (client_t *) arg;

	if (recv(tmpClient->sockfd, name, CLIENT_NAME_SIZE, 0) < 1 || strlen(name) < 2 || strlen(name) >= (CLIENT_NAME_SIZE - 1)) {			/*	name of the client	*/
		write_log("A client hasn't entered the name correctly.", INFO, SERVER_LOG);
		leave_flag = true;
	} else {
		strcpy(tmpClient->name, name);
		sprintf(buff_out, "%s joinded", tmpClient->name);
		printf("%s\n", buff_out);
		send_message(buff_out, tmpClient->uid);
	}

	// memset(buff_out, 0, BUFFER_SIZE);

	do {
		memset(buff_out, 0, BUFFER_SIZE);

		int receivedBytes = recv(tmpClient->sockfd, buff_out, BUFFER_SIZE, 0);
		if (receivedBytes == -1) {
			perror("recv()");
			write_log("receiving message failed", WARNING, SERVER_LOG);
			leave_flag = true;
		} else if (receivedBytes == 0 || (strcmp(buff_out, "exit") == 0)) {
			sprintf(buff_out, "%s left", tmpClient->name);
			printf("%s\n", buff_out);
			send_message(buff_out, tmpClient->uid);
			leave_flag = true;
		} else {
			if (strlen(buff_out) > 0) {
				send_message(buff_out, tmpClient->uid);
				char *last_sign =  strrchr(buff_out, (int) '\n');
				*last_sign = '\0';

				printf("%s -> %s\n", buff_out, tmpClient->name);
			}
		}
	} while(!leave_flag);

	if (close(tmpClient->sockfd) < 0) {																									/*	deleting client from queue	*/
		perror("close()");
		sprintf(buff_out, "closing socket for %s(%d) failed\n", tmpClient->name, tmpClient->uid);
		write_log(buff_out, CRITICAL, SERVER_LOG);
		
		exit(EXIT_FAILURE);
	}

	remove_from_queue(tmpClient->uid);
	free(tmpClient);
	client_ctr--;
	pthread_detach(pthread_self());

	return NULL;
}

int main(int argc, char **argv) {
	init_log();

	if (argc != 3) {
		write_log("server not correctly started", WARNING, SERVER_LOG);
		fprintf(stderr, "usage: %s <ip_address> <port>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int port = strtol(argv[2], NULL, 0);																									/*	using port number	*/
	int option = 1;

	struct sockaddr_in serv_addr, client_addr;
	pthread_t thread_id;

	/*	socket settings	*/
	if ((listen_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket()");
		write_log("socket creation failed", CRITICAL, SERVER_LOG);
		return EXIT_FAILURE;
	}

	atexit(clean_up);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(port);

	signal(SIGPIPE, signal_catcher);
	signal(SIGTERM, signal_catcher);
	signal(SIGKILL, signal_catcher);

	if (setsockopt(listen_fd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (void *) &option, sizeof(option)) < 0) {
		perror("setsockopt()");
		write_log("socket option set failed", CRITICAL, SERVER_LOG);
		return EXIT_FAILURE;
	}

	if (bind(listen_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("bind()");
		write_log("binding address failed", CRITICAL, SERVER_LOG);
		return EXIT_FAILURE;
	}

	if (listen(listen_fd, 10) < 0) {
		perror("listen()");
		write_log("listening for connections failed", CRITICAL, SERVER_LOG);
		return EXIT_FAILURE;
	}

	puts("server chat starting...");
	while(true) {
		printf(" current number of chat users: %d/%d\n", client_ctr, MAX_CLIENTS);

		socklen_t client_length = sizeof(client_addr);
		if ((conn_fd = accept(listen_fd, (struct sockaddr *) &client_addr, &client_length)) < 0) {
			perror("accept()");
			write_log("accepting client request failed", CRITICAL, SERVER_LOG);
			return EXIT_FAILURE;
		}

		if (client_ctr + 1 == MAX_CLIENTS) {
			fprintf(stderr, "Maximum number of clients reached. Rejecting.\n");

			if (close(conn_fd) < 0) {
				perror("close()");
				write_log("closing rejected client failed", CRITICAL, SERVER_LOG);
				return EXIT_FAILURE;
			}

			write_log("maximum number of clients reached", INFO, SERVER_LOG);
			continue;
		}

		client_t *client_to_use = (client_t *) calloc(1, sizeof(client_t));																	/*	client settings	*/
		client_to_use->address = client_addr;
		client_to_use->sockfd = conn_fd;
		client_to_use->uid = uid++;

		add_to_queue(client_to_use);																											/*	add client to queue	*/
		if (pthread_create(&thread_id, NULL, &manage_clients, (void *) client_to_use) < 0) {
			perror("pthread_create()");
			write_log("thread creation failed", CRITICAL, SERVER_LOG);
			return EXIT_FAILURE;
		}

		sleep(1);
	}

	close_log();
	return EXIT_SUCCESS;
}