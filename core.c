#include "shell.h"

/**
* searchfile - Search for a file in a dir_l list
* @head: pointer to the dir_l list
* @name: name of the file
*
* Return: pointer to the file path string, NULL otherwise
* if file was not found
*/
char *searchfile(dir_l *head, char *name)
{
	char *file = NULL;
	int name_len = _strlen(name);
	int file_len = 0, dir_len = 0;

	while (head != NULL)
	{
		dir_len = _strlen(head->dir_name);
		file_len = dir_len + name_len + 2;
		file = malloc(sizeof(*file) * file_len);
		if (!file)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		_memcpy(file, head->dir_name, dir_len);
		_memcpy(file + dir_len, "/", 1);
		_memcpy(file + dir_len + 1, name, name_len + 1);
		file[file_len - 1] = '\0';
		if (isProgramPath(file))
			return (file);
		free(file);
		file = NULL;
		head = head->next;
	}

	return (NULL);
}

/**
* isProgramPath - Checks if the path specified
* is the actual path to the program
* @path: Path to the program
*
* Return: path to the specified program
*/
int isProgramPath(char *path)
{
	if (access(path, X_OK) == 0)
		return (1);
	return (0);
}

/**
* search_prog - Looks for a program in the process environment
* @command: The user command input
* @tokens: The user command input tokens
* @argv: NULL terminated list of the shell's arguments
*
* Return: Pointer to the updated program name token
*/
char *search_prog(char *command, char **tokens, char *argv[])
{
	char *env_path = _getenv(ENV_PATH);
	char *prog_path = NULL;
	dir_l *head = NULL;

	if (!tokens || !env_path)
		return (NULL);
	if (execute_builtin_command(command, tokens, env_path))
	{
		return (NULL);
	}
	if (isProgramPath(tokens[0]))
	{
		free(env_path);
		return (_strdup(tokens[0]));
	}
	build_env_dirs(&head, env_path);
	prog_path = searchfile(head, tokens[0]);
	if (prog_path == NULL)
	{
		showError(argv[0], tokens[0]);
		free_dirl(&head);
		free(env_path);
		return (NULL);
	}
	free_dirl(&head);
	free(env_path);
	return (prog_path);
}
