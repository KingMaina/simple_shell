#include "shell.h"

/**
* free_memory - De-allocates memory fro a buffer
* @buffer: Null terminated string
*
* Return: void
*/
void free_memory(char **buffer)
{
	if (*buffer != NULL)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

/**
* free_dirl - De-allocates memory from a dir_l linked list
* @head: Pointer to the head node address of the linked list
*
* Return: void
*/
void free_dirl(dir_l **head)
{
	dir_l *curr_ptr = NULL;
	dir_l *next_ptr = NULL;

	if (!head || !(*head))
		return;
	curr_ptr = *head;
	next_ptr = (*head)->next;
	while (next_ptr != NULL)
	{
		free(curr_ptr->dir_name);
		free(curr_ptr);
		curr_ptr = next_ptr;
		next_ptr = next_ptr->next;
	}
	free(curr_ptr->dir_name);
	free(curr_ptr);
	*head = NULL;
}

/**
* free_args - De-allocates memory from an array of strings
* allocated dynamically
* @args: the address of a pointer to an array of strings
*
* Description: Using a tripple pointer allos us to fully
* control the args variable and help us de-allocate memory
* of the array of strings it points to and also reset the
* args
*
* Return: void
*/
void free_args(char ***args)
{
	int i;
	char **current_arg;

	if (args == NULL || *args == NULL)
		return;
	current_arg = *args;
	i = 0;
	while (current_arg[i] != NULL)
		free(current_arg[i++]);
	free(*args);
	*args = NULL;
}

/**
 * free_tokens - frees the memory allocated for tokens
 * @tokens: tokens to be freed
 */
void free_tokens(char **tokens)
{
	int i = 0;

	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

/**
 * cleanup - Free the dynamically allocated memory for the command, arguments,
 * and program path.
 * @command: commands to be freed
 * @progPath: path to free
 * @args: ...
 *
 * Return: nothing
 */
void cleanup(char *command, char **args, char *progPath)
{
	free(command);
	free_args(&args);
	free(progPath);
}
