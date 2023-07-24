#include "shell.h"

#define MAX_TOKENS 100
#define DELIMS " \t\r\n"

/**
 * split_string - a function that tokenizes input to the shell
 * @str: input string with command and arguments
 * @num_args: counts the number of arguments
 *
 * Return: tokens
 */

char **split_string(char *str, int *num_args)
{
	char **tokens = malloc(MAX_TOKENS * sizeof(char *));
	char *token;
	int token_position = 0;

	if (tokens == NULL)
	{
		perror("split string: failed to allocate memory for tokens");
		exit(EXIT_FAILURE);
	}
	token = strtok(str, DELIMS);
	while (token != NULL)
	{
		if (token_position >= MAX_TOKENS)
		{
			perror("split_string: too many tokens, limit is 100");
			exit(EXIT_FAILURE);
		}
		if (token[0] == '"' && token[_strlen(token) - 1] == '"')
		{
			token[strlen(token) - 1] = '\0';
			token++;
		}
		tokens[token_position] = _strdup(token);

		if (!tokens[token_position])
		{
			while (token_position > 0)
				free(tokens[--token_position]);
			free(tokens);
			return (NULL);
		}
		token_position++;
		token = strtok(NULL, DELIMS);
	}
	tokens[token_position] = NULL;
	*num_args = token_position;

	return (tokens);
}
