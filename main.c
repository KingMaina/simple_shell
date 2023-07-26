#include "shell.h"

static int last_exit_status;

/**
 * set_last_exit_status - Function to set the last exit status
 * @status: status
 *
 * Return: ...
 */
void set_last_exit_status(int status)
{
	last_exit_status = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

/**
 * get_last_exit_status - Function to get the last exit status
 *
 * Return: last exit status
 */
int get_last_exit_status(void)
{
	return (last_exit_status);
}
/**
 * process_command - handles the prcoessing of each command
 * @command: comands from user
 * @argv: NULL terminated list of the application arguments
 * @env: NULL terminated list of the process' environment variables
 *
 * Return: none
 */
void process_command(char *command, char **argv, char **env)
{
	int num_args;
	char **args = NULL;
	char *progPath = NULL;

	if (!command || command[0] == '\0')
	{
		free(command);
		return;
	}
	num_args = 0;
	args = split_string(command, &num_args);
	progPath = search_prog(args[0], argv);

	if (progPath == NULL)
	{
		free(command);
		free_tokens(args);
		return;
	}
	update_cmd(args, 0, progPath);
	execute_command(args, env);

	if (_strcmp(args[0], "exit") == 0)
	{
		cleanup(command, args, progPath);
		exitShell(args);
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
		signal(SIGINT, handle_sigint);
		prompt();
		command = read_command();
		if (command == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		process_command(command, argv, env);
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
int main(UN_ATTR int argc, char **argv, char **env)
{
	last_exit_status = 0;
	shell_loop(env, argv);

	return (EXIT_SUCCESS);
}
