#ifndef CLIENT_H
#define CLIENT_H

#define	BUFFER_LENGTH		2048
#define NAME_LENGTH			32
#define	CLIENT_DISCONNECTED	0

/*	function prototypes		*/
void *send_message(void *arg);
void *receive_message(void *arg);

#endif