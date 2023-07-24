#include "shell.h"

/**
* prompt - Prompts the user to enter a command
*
* Return: void
*/
void prompt(void)
{
	int prompt_len = 2;

	write(STDOUT_FILENO, "$ ", prompt_len);
	fflush(stdout);
}


/**
* update_cmd - Updates a command argument
* @args: Pointer to the argument array
* @index: index of the token command
* @arg: value to update argument
*
* Return: void
*/
void update_cmd(char **args, int index, char *arg)
{
	if (!args || !(*args) || !arg || index < 0)
		return;
	free(args[index]);
	args[index] = _strdup(arg);
}

/**
 * read_command -reads command from the user
 *
 * Return: command
 */
char *read_command(void)
{
	char *command = NULL;
	size_t command_len = 0;
	ssize_t bytesRead = -1;

	while (1)
	{
		bytesRead = getline(&command, &command_len, stdin);

		if (bytesRead == -1)
		{
			free(command);
			return (NULL);
		}
		if (command[bytesRead - 1] == '\n')
			command[bytesRead - 1] = '\0';

		fflush(stdin);

		break;
	}
	return (command);
}
