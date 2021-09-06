#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#include "chat.h"
#include "logger.h"

static FILE *out_server = NULL;
static FILE *out_client = NULL;
static struct tm *current_time = NULL;
static DIR *log_directory = NULL;

void init_log(void) {
	log_directory = opendir(LOG_FOLDER);																		/*	check, if the log directory already exists	*/
	if (log_directory == NULL) {																				/*	if not, then try to create the folder		*/
		if (mkdir(LOG_FOLDER, 0777) < 0) {																		/*	if fails, then abort the application		*/
			perror("mkdir()");
			abort();
		}
	}

	if (chdir(LOG_FOLDER) < 0) {																				/*	go to the log folder						*/
		perror("chdir()");
		abort();
	}

	if ((out_server = fopen(LOG_FILE_SERVER, "a")) == NULL) {
		perror("fopen() server");
		abort();
	}
	
	if ((out_client = fopen(LOG_FILE_CLIENT, "a")) == NULL) {
		perror("fopen() client");
		abort();
	}

	time_t rawtime = time(NULL);
	assert(rawtime != -1);

	current_time = localtime(&rawtime);
	assert(current_time != NULL);
}

void close_log(void) {
	fclose(out_server);
	fclose(out_client);
	closedir(log_directory);

	out_server = NULL;
	out_client = NULL;

	current_time = NULL;
}

void write_log(const char *message, ErrorLevel errorLevel, ComputerLogDestination computer_type) {
	char buffer[LOG_BUFFER_SIZE] = {'\0'};
	strftime(buffer, LOG_BUFFER_SIZE, "%x %X ", current_time);
	
	switch (errorLevel) {
		case INFO:
			strcat(buffer, "INFO: ");
			break;
		case WARNING:
			strcat(buffer, "WARNING: ");
			break;
		case CRITICAL:
			strcat(buffer, "CRITICAL: ");
			break;
	}

	strcat(buffer, message);
	strcat(buffer, "\n");

	switch (computer_type) {
		case SERVER_LOG:
			fprintf(out_server, "%s", buffer);
			break;
		case CLIENT_LOG:
			fprintf(out_client, "%s", buffer);
			break;
	}
}