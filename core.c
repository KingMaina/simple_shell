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
		_strncpy(file, head->dir_name, dir_len);
		_strcat(file + dir_len, "/");
		_strcat(file + dir_len + 1, name);
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
* @name: Name of the program
*
* Return: Pointer to the updated program name token
*/
char *search_prog(char *name)
{
	char *env_path = _getenv(ENV_PATH);
	char *prog_path = NULL;
	dir_l *head = NULL;
	char **args = malloc(sizeof(char *) * 2);

	if (!name || !env_path)
		return (NULL);

	args[0] = name;
	args[1] = NULL;

	if (execute_builtin_command(args))
	{
		free(env_path);
		return _strdup(name);
	}
	if (isProgramPath(name))
	{
		free(env_path);
		return (_strdup(name));
	}
	build_env_dirs(&head, env_path);
	prog_path = searchfile(head, name);

	if (prog_path == NULL)
	{
		fprintf(stderr, "bash: %s: %s\n", name, strerror(errno));
		free_dirl(&head);
		free(env_path);
		return (NULL);
	}

	free_dirl(&head);
	free(env_path);
	return (prog_path);
}
