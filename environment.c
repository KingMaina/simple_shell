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
