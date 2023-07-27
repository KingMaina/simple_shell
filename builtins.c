#include "shell.h"

/**
 * handle_exit - handles the exit built-in
 * @args: the command and its arguments
 * @argv: NULL terminated list of the shell's arguments
 *
 * Return: nothing
*/
void handle_exit(char **args, char **argv)
{
	int exit_code = 0;

	if (args[1])
	{
		exit_code = _atoi(args[1]);
		if (exit_code < 0 && args[1][0] != '0')
		{
			exit_code = 2;
			write(STDERR_FILENO, argv[0], _strlen(argv[0]));
			write(STDERR_FILENO, ": 1: ", 5);
			write(STDERR_FILENO, args[0], _strlen(args[0]));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, "Illegal number: ", 16);
			write(STDERR_FILENO, args[1], _strlen(args[1]));
			write(STDERR_FILENO, "\n", 1);
		}
		else if (exit_code > 255)
			exit_code = 232;
	}
	else
	{
		exit_code = 2;
	}
	free_tokens(args);
	exit(exit_code);
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

/**
 * handle_cd - handles te change diectory built-in
 * @args: the command an d its arguments
 *
 * Return: 0 success, -1 failure
 */

int handle_cd(char **args)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);

	if (!s)
	{
		write(STDERR_FILENO, "cd: Failed to get current working directory\n", 45);
		return (-1);
	}
	if (!args[1])
	{
		dir = _getenv("HOME");
		if (!dir)
		{
			write(STDERR_FILENO, "cd: HOME environment variable not set\n", 38);
			return (-1);
		}
		chdir_ret = chdir(dir);
	}
	else if (_strcmp(args[1], "-") == 0)
	{
		dir = _getenv("OLDPWD");
		if (!dir)
		{
			write(STDERR_FILENO, "cd: OLDPWD environment variable not set\n", 40);
			return (-1);
		}
		write(STDOUT_FILENO, dir, _strlen(dir));
		write(STDOUT_FILENO, "\n", 1);
		chdir_ret = chdir(dir);
	}
	else
	{
		chdir_ret = chdir(args[1]);
	}
	if (chdir_ret == -1)
	{
		write(STDERR_FILENO, "cd: ", 4);
		write(STDERR_FILENO, args[1], strlen(args[1]));
		write(STDERR_FILENO, ": No such file or directory\n", 28);
		return (-1);
	}
	else
	{
		setenv("OLDPWD", s, 1);
		setenv("PWD", getcwd(buffer, 1024), 1);
	}

	return (0);
}
