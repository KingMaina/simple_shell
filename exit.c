#include "shell.h"

#define CONTINUE_COMMAND 0
#define EXIT_COMMAND 1
/**
 * exitShell - exit built-in, that exits the shell
 * @arg: array of words of the entered shell
 *
 * Return: nothing
 */

void exitShell(char **arg)
{
	char command[100];
	int i = 1;
	int exit_code = 0;
	char exitMessage[] = "exit\n\n[Disconnected...]\n";

	read(STDIN_FILENO, command, sizeof(command));
	command[_strcspn(command, "\n")] = '\0';

	if (_strcmp(command, "exit") == 0)
	{
		if (arg[i])
		{
			exit_code = _atoi(arg[i]);
			if (exit_code <= -1)
				exit_code = 2;
		}
		free_args2(arg);
		write(STDOUT_FILENO, exitMessage, sizeof(exitMessage) - 1);
		exit(get_last_exit_status());
	}
}

/**
 * free_args2 - De-allocates memory from an array of strings
 * allocated dynamically
 * @arg: the address of a pointer to an array of strings
 *
 * Description: This function de-allocates memory from the array of strings
 * and sets the `arg` pointer to NULL.
 *
 * Return: void
 */
void free_args2(char **arg)
{
	int i;

	if (arg == NULL)
		return;

	i = 0;
	while (arg[i] != NULL)
		free(arg[i++]);

	free(arg);
	*arg = NULL;
}
