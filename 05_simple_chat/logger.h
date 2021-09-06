#ifndef LOGGER_H
#define LOGGER_H

#define LOG_FOLDER			"logs"
#define LOG_FILE_SERVER		"server.log"
#define LOG_FILE_CLIENT		"client.log"
#define LOG_BUFFER_SIZE		1024

void init_log(void);
void close_log(void);

#endif