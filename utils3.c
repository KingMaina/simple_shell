/**
 * _atoi - Converts a string to an integer
 * @str: The string to be converted
 *
 * Return: The converted integer
 */
int _atoi(const char *str)
{
	int sign = 1;
	int result = 0;
	int i = 0;

	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}

	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result = result * 10 + (str[i] - '0');
			i++;
		}
		else
		{
			break;
		}
	}

	return (sign * result);
}
