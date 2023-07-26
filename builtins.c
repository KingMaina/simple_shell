#include "shell.h"

/**
 * handle_exit - handles the exit built-in
 * @args: the command and its arguments
 *
 * Return: nothing
*/
void handle_exit(char **args)
{
	if (args[1] == NULL)
	{
		free_tokens(args);
		exit(EXIT_SUCCESS);
	}
}

/**
* handle_env - Prints the process' environment variables
*
* Return: nothing
*/
void handle_env(void)
{
	int i = 0;

	while (environ[i])
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
