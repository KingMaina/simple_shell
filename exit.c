#include "shell.h"

#define CONTINUE_COMMAND 0
#define EXIT_COMMAND 1
/**
 * exitShell - exit built-in, that exits the shell
 *
 * Return: nothing
 */

void exitShell(void)
{
	char command[100];
	char exitMessage[] = "exit\n\n[Disconnected...]\n";

	read(STDIN_FILENO, command, sizeof(command));
	command[strcspn(command, "\n")] = '\0';

	if (strcmp(command, "exit") == 0)
	{
		write(STDOUT_FILENO, exitMessage, sizeof(exitMessage) - 1);
		_exit(EXIT_SUCCESS);
	}
	else
	{
		handleCommand(command);
	}
}

/**
 * custom_error - a function that handles errors
 * @arg: ...
 * @message: ...
 *
 * Return: nothing
 */
void custom_error(const char *arg, const char *message)
{
	write(STDOUT_FILENO, "bash: exit: ", sizeof("bash: exit: ") - 1);
	write(STDOUT_FILENO, arg, strlen(arg));
	write(STDOUT_FILENO, ": ", sizeof(": ") - 1);
	write(STDOUT_FILENO, message, strlen(message));
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * handleCommand - Handles custom commands in the shell
 * @command: The command to be handled
 *
 * Return: None
 */

int handleCommand(const char *command)
{
	int exit_code;
	const char *arg;
	size_t i;

	if (_strncmp(command, "exit", 4) == 0)
	{
		arg = command + 4;
		while (*arg && (*arg == ' ' || *arg == '\t'))
		{
			arg++;
		}
		if (*arg)
		{
			for (i = 0; arg[i] != '\0'; i++)
			{
				if (arg[i] < '0' || arg[i] > '9')
				{
					custom_error(arg, "numeric argument required");
					return (CONTINUE_COMMAND);
				}
			}
			exit_code = atoi(arg);
			if (exit_code >= 0 && exit_code <= 255)
			{
				return (EXIT_COMMAND);
			}
			else
			{
				custom_error(arg, "status out of range: 0-255");
				return (CONTINUE_COMMAND);
			}
		}
		else
		{
			return (EXIT_COMMAND);
		}
	}
	return (CONTINUE_COMMAND);
}
