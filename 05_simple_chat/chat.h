#ifndef CHAT_H
#define CHAT_H

typedef enum ErrLevel {
	INFO = 1,
	WARNING = 2,
	CRITICAL = 4
} ErrorLevel;

typedef enum ErrComputer {
	SERVER_LOG = 8,
	CLIENT_LOG = 16
} ComputerLogDestination;

void write_log(const char *log_text, ErrorLevel error_level, ComputerLogDestination computer_type);

#endif