#include "shell.h"


/**
 * process_command - handles the prcoessing of each command
 * @command: comands from user
 * @env: NULL terminated list of the process' environment variables
 *
 * Return: none
 */
void process_command(char *command, char **env)
{
	int num_args;
	char **args;
	char *progPath;

	if (command == NULL || command[0] == '\n')
	{
		free(command);
		return;
	}
	num_args = 0;
	args = split_string(command, &num_args);
	progPath = search_prog(args[0]);

	if (progPath == NULL)
	{
		return;
	}
	update_cmd(args, 0, progPath);
	execute_command(args, env);

	if (_strcmp(args[0], "exit") == 0)
	{
		cleanup(command, args, progPath);
		exitShell();
	}
	cleanup(command, args, progPath);
}

/**
 * shell_loop - handles the main loop in the entry point
 * @argv: NULL terminated list of the application arguments
 * @env: NULL terminated list of the process' environment variables
 *
 * Return: nothing
 */
void shell_loop(char **env, char *argv[])
{
	char *command;

	while (1 && argv[0])
	{
		prompt();
		command = read_command();
		process_command(command, env);
	}
}

/**
* main - Entry of shell application
* @argc: Number of arguments passed to the program
* @argv: NULL terminated list of the application arguments
* @env: NULL terminated list of the process' environment variables
*
* Return: 0 if successful, non-zero if error
*/
int main(__attribute__((unused)) int argc, char **argv, char **env)
{
	shell_loop(env, argv);

	return (EXIT_SUCCESS);
}
