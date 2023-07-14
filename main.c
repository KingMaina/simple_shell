#include "shell.h"

/**
* main - Entry of shell application
* @argc: Number of arguments passed to the program
* @argv: NULL terminated list of the application arguments
* @env: NULL terminated list of the process' environment variables
*
* Return: 0 if successful, non-zero if error
*/
int main(int argc, char **argv, __attribute__((unused)) char **env)
{
	char *command = NULL, *progPath = NULL;
	size_t command_len = 0;
	ssize_t bytesRead = -1;
	char **args = NULL;
	int num_args;

	(void)argc;
	while (1 && argv[0])
	{
		prompt();
		bytesRead = getline(&command, &command_len, stdin);
		if (bytesRead == -1)
		{
			free(command);
			command_len = 0;
			write(STDOUT_FILENO, "\n", 1);
			break;
		}
		if (command[0] == '\n')
			continue;
		args = split_string(command, &num_args);
		progPath = search_prog(args[0]);
		if (progPath == NULL)
		{
			free_args(&args);
			continue;
		}
		update_cmd(args, 0, progPath);
		execute_command(args, env);
		free_args(&args);
		free(progPath);
		progPath = NULL;
		free(command);
		command = NULL;
	}

	return (EXIT_SUCCESS);
}
