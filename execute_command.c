#include "shell.h"

/**
 * execute_builtin_command - searches if the given command by
 * user is in-built
 * @args: null-terminate array of strings containing command and its arguments
 *
 * Return: 1 success, 0 otherwise
 */

int execute_builtin_command(char **args)
{
	char *cmd = args[0];
	char error_message[100];

	if (cmd == NULL)
	{
		return (0);
	}
	if (_strcmp(cmd, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}

	if (_strcmp(cmd, "cd") == 0)
	{
		if (args[1] == NULL)
		{
			return (1);
		}
		else
		{
			if (chdir(args[1]) != 0)
			{
				_strcpy(error_message, "cd: ");
				_strcat(error_message, args[1]);
				_strcat(error_message, ": ");
				_strcat(error_message, strerror(errno));
				_strcat(error_message, "\n");
				write(STDERR_FILENO, error_message,
				      _strlen(error_message));
			}
		}
		return (1);
	}
	return (0);
}

/**
 * execute_external_command - searches for executables in the system path
 * @args: null-terminate array of strings containing command and its arguments
 * @env: a pointer to an array of strings of environment variables
 * Return: pointer to path of executable file, NULL if not found
 */

int execute_external_command(char **args, char **env)
{
	pid_t pid;
	char *program_path = search_prog(args[0]);

	if (program_path == NULL)
	{
		char *msg = _strcat(args[0], ": command not found\n");

		write(STDERR_FILENO, msg, _strlen(msg));
		free(msg);
		return (0);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	if (pid == 0)
	{
		if (execve(program_path, args, env) == -1)
		{
			perror(program_path);
			return (0);
		}
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
	free(program_path);
	return (1);
}

/**
 * execute_command - a function that combines built-in and external commands
 * @args: null-terminate array of strings containing command and its arguments
 * @env: a pointer to an array of strings of environment variables
 * Return: 1 success, O otherwise
 */

int execute_command(char **args, char **env)
{
	if (execute_builtin_command(args))
	{
		return (1);
	}

	if (execute_external_command(args, env))
	{
		return (1);
	}
	return (0);
}
