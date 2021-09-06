#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "chat.h"
#include "logger.h"
#include "client.h"

/*	global variables	*/
static int sockfd = 0;
static char name[NAME_LENGTH] = {'\0'};

void clean_up(void) {
	if (close(sockfd) < 0) {
		perror("close()");
		write_log("failed to close client socket", CRITICAL, CLIENT_LOG);
		exit(EXIT_FAILURE);
	}
}

void string_overwrite_stdout(void) {
	printf("==> ");
	fflush(stdout);
}

void handle_signal(int sig_nbr) {
	char buffer[BUFFER_LENGTH/4] = {'\0'};

	if (sig_nbr != CLIENT_DISCONNECTED) {
		sprintf(buffer, "Received signal: %s(%d)", strsignal(sig_nbr), sig_nbr);
	} else {
		sprintf(buffer, "client (%s) disconnected\n", name);
	}

	printf("%s\n", buffer);
	write_log(buffer, INFO, CLIENT_LOG);
	exit(sig_nbr);
}

void *send_message(void *arg) {
	char message[BUFFER_LENGTH] = {'\0'};
	char buffer[BUFFER_LENGTH + NAME_LENGTH] = {'\0'};

	while(true) {
		string_overwrite_stdout();
		fgets(message, BUFFER_LENGTH, stdin);
		char *lastChar = strrchr(message, '\n');
		*lastChar = '\0';

		if(strcmp(message, "exit") == 0) {
			handle_signal(CLIENT_DISCONNECTED);
		}

		sprintf(buffer, "%s: %s\n", name, message);
		if (send(sockfd, buffer, strlen(buffer), 0) < 0) {
			perror("send()");
			write_log("sending message failed", WARNING, CLIENT_LOG);
			break;
		}

		memset(message, 0, BUFFER_LENGTH);
		memset(message, 0, BUFFER_LENGTH + NAME_LENGTH);
	}

	return NULL;
}

void *receive_message(void *arg) {
	char message[BUFFER_LENGTH] = {'\0'};
	while(true) {
		int receive = recv(sockfd, message, BUFFER_LENGTH, 0);

		if (receive < 0) {
			perror("recv()");
			write_log("receiving message failed", WARNING, CLIENT_LOG);
		} else if (receive == 0) {
			fprintf(stderr, "Connection lost.\n");
			write_log("Connection lost.", WARNING, CLIENT_LOG);
			break;
		} else {
			printf("%s\n", message);
			string_overwrite_stdout();
		}

		memset(message, 0, sizeof(message));
	}

	return NULL;
}

int main(int argc, char **argv) {
	init_log();

	if (argc != 3) {
		write_log("client not correctly started", WARNING, CLIENT_LOG);
		fprintf(stderr, "usage: %s <ip_address> <port>\n", argv[0]);
		return EXIT_FAILURE;
	}

	int port_number = strtol(argv[2], NULL, 0);
	signal(SIGPIPE, handle_signal);
	signal(SIGTERM, handle_signal);
	signal(SIGKILL, handle_signal);

	printf("Please enter your name: ");
	fgets(name, NAME_LENGTH, stdin);

	char *last_character = strrchr(name, (int) '\n');
	*last_character = '\0';

	if (strlen(name) > NAME_LENGTH || strlen(name) < 2) {
		fprintf(stderr, "Your name must have a length between 2 and %d\n", NAME_LENGTH);
		write_log("client name length out of bounds", INFO, CLIENT_LOG);
		return EXIT_FAILURE;
	}

	struct sockaddr_in server_addr;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {																					/*	socket settings	*/
		perror("socket()");
		write_log("socket creation failed", CRITICAL, CLIENT_LOG);
		return EXIT_FAILURE;
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	server_addr.sin_port = htons(port_number);

	if (connect(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {														/*	connect to the server	*/
		perror("connect()");
		write_log("connection to the server failed", CRITICAL, CLIENT_LOG);
		return EXIT_FAILURE;
	}

	if (send(sockfd, name, NAME_LENGTH, 0) < 0) {																							/*	sending message			*/
		perror("send()");
		write_log("sending message failed", CRITICAL, CLIENT_LOG);
		return EXIT_FAILURE;
	}

	puts(".:WELCOME TO THE CHAT ROOM:.");
	puts(" quit with: exit\n to talk with an another client, type: >client: message");
	pthread_t send_message_thread;

	if (pthread_create(&send_message_thread, NULL, send_message, NULL) != 0) {
		perror("pthread_create()");
		write_log("thread creation sending message failed", CRITICAL, CLIENT_LOG);
		return EXIT_FAILURE;
	}

	if (pthread_create(&send_message_thread, NULL, receive_message, NULL) != 0) {
		perror("pthread_create()");
		write_log("thread creation receiving message failed", CRITICAL, CLIENT_LOG);
		return EXIT_FAILURE;
	}

	if (pthread_join(send_message_thread, NULL) != 0) {
		perror("pthread_join()");
		write_log("join thread failed", CRITICAL, CLIENT_LOG);
		return EXIT_FAILURE;
	}

	close_log();
	return EXIT_SUCCESS;
}