/**
 * strcnl - remove new line charater from string
 * @str: string to parse
 * Return: modified string
*/
char *strcnl(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 10)
			str[i] = 0;
		i++;
	}

	return (str);
}
