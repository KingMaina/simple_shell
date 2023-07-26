#include "shell.h"

/**
* handle_sigint - handles the signal
* @sig: signal
*
* Return: nothing
*/
void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}

