#include "shell.h"

/**
 * execute_builtin_command - searches if the given command by
 * user is in-built
 * @command: command given by user
 * @args: null-terminate array of strings containing command and its arguments
 * @env_path: pointer to the path of the environment
 * @argv: NULL terminated list of the shell's arguments
 *
 * Return: 1 success, 0 otherwise
 */

int execute_builtin_command(char *command,
char **args, char *env_path, char **argv)
{
	char *cmd = args[0];
	char error_message[100];

	if (cmd == NULL)
		return (0);
	if (_strcmp(cmd, "exit") == 0)
	{
		free(env_path);
		free(command);
		handle_exit(args, argv);
		return (1);
	}
	if (_strcmp(cmd, "cd") == 0)
	{
		if (args[1] == NULL)
			return (1);
		else if (chdir(args[1]) != 0)
		{
			_strcpy(error_message, "cd: ");
			_strcat(error_message, args[1]);
			_strcat(error_message, ": ");
			_strcat(error_message, strerror(errno));
			_strcat(error_message, "\n");
			write(STDERR_FILENO, error_message,
			_strlen(error_message));
		}
		return (1);
	}
	if (_strcmp(cmd, "env") == 0)
	{
		free(env_path);
		handle_env();
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
	int status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (0);
	}
	if (pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		set_last_exit_status(status);
	}
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
	if (execute_external_command(args, env))
		return (1);
	return (0);
}
