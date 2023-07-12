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
