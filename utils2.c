#include "shell.h"

/**
* _strncmp - Compare n bytes from two string
* @s1: The first string
* @s2: The second string
* @n: The number of bytes to compare
*
* Return: 0 if the strings exaclty match upto the nth byte
*/
int _strncmp(const char *s1, char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] < s2[i] ? -1 : 1);
		if (s1[i] == '\0')
			return (0);
	}
	return (0);
}

/**
  * _strchr - locate character in string
  * @s: source string
  * @c: character to find
  *
  * Return: the string from character found
  */

char *_strchr(char *s, char c)
{
	int a = 0, b;

	while (s[a])
	{
		a++;
	}

	for (b = 0; b <= a; b++)
	{
		if (c == s[b])
		{
			s += b;
			return (s);
		}
	}

	return ('\0');
}

/**
 * _strncpy - a function that copies from src to dest
 * @src: source file
 * @dest: destination file
 * @n: copy limit
 *
 * Return: pointer to destinatiom
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	{
		dest[i] = src[i];
	}
	for (; i < n; i++)
	{
		dest[i] = '\0';
	}

	return (dest);
}

/**
 * _strcpy - Copies the source string to the destination buffer
 * @dest: Destination buffer
 * @src: Source string
 *
 * Return: Pointer to the destination buffer
 */
char *_strcpy(char *dest, const char *src)
{
	char *ptr = dest;

	while (*src != '\0')
	{
		*ptr = *src;
		ptr++;
		src++;
	}

	*ptr = '\0';

	return (dest);
}

/**
 * _strcspn - searches for the first occurrence of any character
 * @str: ...
 * @reject: ...
 *
 * Return: returns the position (index) of the first occurrence
 */
size_t _strcspn(const char *str, const char *reject)
{
	size_t i, j;

	for (i = 0; str[i] != '\0'; i++)
	{
		for (j = 0; reject[j] != '\0'; j++)
		{
			if (str[i] == reject[j])
			{
				return (i);
			}
		}
	}
	return (i);
}
