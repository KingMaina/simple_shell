#include "shell.h"

/**
* _strlen - Counts the length of a string
* @str: string
*
* Return: Number of bytes counted
*/
size_t _strlen(char *str)
{
	size_t len = 0;

	while (*str++ != '\0')
		len++;

	return (len);
}

/**
* *_memcpy - copies a specified number of bytes from one string to another.
* @dest: destination string to copy memory area to.
* @src: source string to copy memory area from.
* @n: The number of bytes to copy.
*
* Return: A pointer to the destination string.
*/
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}

	return (dest);
}

/**
* _strcmp - compares two strings in lexical order.
* @s1: The first string.
* @s2: The second string.
*
* Return: 0 if the strings are equal, otherwise the lexical (alphabetical)
* difference in the order of the strings.
*/
int _strcmp(char *s1, char *s2)
{
	while (*s1)
	{
		if (*s1 == *s2)
		{
			s1++;
			s2++;
			continue;
		}
		break;
	}
	return (*s1 - *s2);
}

/**
*  _strcat - concatenates two strings.
*  @dest: The destination string.
*  @src: The source string.
*
* Return: A pointer to the destination string.
*/
char *_strcat(char *dest, char *src)
{
	size_t dest_len = _strlen(dest);
	size_t src_len = _strlen(src);
	size_t i;

	for (i = 0; i < src_len; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';
	return (dest);
}

/**
* _strdup - duplicates a string
* @src: The string to duplicate
*
* Return: The duplicated string, NULL otherwise
*/
char *_strdup(char *src)
{
	size_t len = _strlen(src) + 1;
	char *dest = malloc(sizeof(*dest) * len);

	if (dest)
		_memcpy(dest, src, len);

	return (dest);
}
