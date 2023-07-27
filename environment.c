#include "shell.h"

/**
* _getenv - Searches the environment variable specified
* @name: The environment variable
*
* Return: Pointer to the start of the env variable's value,
* NULL otherwise
*/
char *_getenv(char *name)
{
	int i = 0;
	int name_len = _strlen(name);
	char *path = NULL;

	while (environ[i] != NULL)
	{
		if (_strncmp(environ[i], name, name_len) == 0)
		{
			path = _strdup(environ[i] + name_len + 1);
			return (path);
		}
		i++;
	}

	return (NULL);
}

/**
* add_node_begin - Adds a new node to the start of a
* dir_l linked list
* @head: Pointer to the head node's address
* @str: String to add to the node
*
* Return: Pointer to the created node
*/
dir_l *add_node_begin(dir_l **head, char *str)
{
	dir_l *node = NULL;

	if (str == NULL)
	{
		fprintf(stderr, "Cannot create an empty node\n");
		return (NULL);
	}
	node = malloc(sizeof(dir_l));
	if (node == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	node->dir_name = _strdup(str);
	if (*head == NULL)
	{
		node->next = NULL;
		*head = node;
	}
	else
	{
		node->next = *head;
		*head = node;
	}
	return (node);
}

/**
* build_env_dirs - Creates a linked list from a delimetered string
* @head: Pointer to the head node of a dir_l linked list
* @str: Delimetered string
*
* Return: Pointer to the start of the linked list, NULL otherwise on error
*/
dir_l *build_env_dirs(dir_l **head, char *str)
{
	char *token = strtok(str, DELIM_DIRS);

	if (*head != NULL)
	{
		fprintf(stderr, "List is not empty...");
		return (NULL);
	}
	while (token != NULL)
	{
		add_node_begin(head, token);
		token = strtok(NULL, DELIM_DIRS);
	}
	return (*head);
}

/**
 * _setenv - Sets the value of an environment variable
 * @name: The name of the environment variable
 * @value: The value to set for the environment variable
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value)
{
	char *env_str = NULL;
	int i, name_len = _strlen(name);
	int value_len = _strlen(value);

	if (!name || !value)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], name, name_len) == 0)
		{
			env_str = malloc(name_len + value_len + 2);
			if (!env_str)
				return (-1);

			_strncpy(env_str, name, name_len);
			env_str[name_len] = '=';
			_strcpy(env_str + name_len + 1, value);

			free(environ[i]);
			environ[i] = env_str;
			return (0);
		}
	}
	env_str = malloc(name_len + value_len + 2);
	if (!env_str)
		return (-1);

	_strncpy(env_str, name, name_len);
	env_str[name_len] = '=';
	_strcpy(env_str + name_len + 1, value);

	for (i = 0; environ[i]; i++)
		;
	environ[i] = env_str;
	environ[i + 1] = NULL;
	return (0);
}

/**
 * _unsetenv - Unsets an environment variable
 * @name: The name of the environment variable to unset
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
	int i, j, name_len = _strlen(name);

	if (!name)
		return (-1);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];

			return (0);
		}
	}
	return (-1);
}
