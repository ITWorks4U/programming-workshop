#ifndef SERVER_H
#define SERVER_H

#define	MAX_CLIENTS			10
#define	BUFFER_SIZE			2048																						/*	should be enough...						*/
#define CLIENT_NAME_SIZE	32

#include <sys/socket.h>
#include <netinet/in.h>

typedef struct ClientManager {											
	struct sockaddr_in address;																							/*	address to store required infos			*/
	int sockfd;																											/*	socket file descriptor to use			*/
	int uid;																											/*	client user id							*/
	char name[CLIENT_NAME_SIZE];																						/*	client name								*/
} client_t;

client_t *clients[MAX_CLIENTS];

/*	function prototypes	*/											
void signalCatcher(int signalNumber);																					/*	catching any system signal				*/
void add_to_queue(client_t *single_client);																				/*	add client n to the queue				*/
void remove_from_queue(const int userid);																				/*	remove client n from the queue			*/

void *manage_clients(void *arg);																						/*	thread function for client(s)			*/

//	not implemented yet
// bool message_contains_name(const char *client_message);																	/*	the message contains a '>(name):'		*/
// void manage_target_client(char *client_name, char *message, unsigned int start_pos, unsigned int end_pos);				/*	Which client wants to be chatted with?	*/

#endif