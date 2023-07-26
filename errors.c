#include "shell.h"

/**
 * showError - Prints an error message to stderr
 * @program: name of program
 * @command: command that failed
 *
 * Return: nothing
*/
void showError(char *program, char *command)
{
	char error_message[1024];
	int program_len = 0, command_len = 0;

	if (program == NULL || command == NULL)
		return;
	program_len = _strlen(program);
	command_len = _strlen(command);
	_strncpy(error_message, program, program_len);
	_memcpy(error_message + program_len, ": 1: ", 5);
	_memcpy(error_message + program_len + 5, command, command_len);
	_memcpy(error_message + program_len + 5 + command_len,
	": not found\n", 13);
	write(STDERR_FILENO, error_message, _strlen(error_message));
}
