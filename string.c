#include "main.h"

/**
 * _strlen - computes the length of a string
 * @s: string which length to compute
 * Return: length of s
*/
int _strlen(char *s)
{
	int len;

	len = 0;
	while (*s)
	{
		len++;
		s++;
	}

	return (len);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _putstr - print string (without new line)
 * @s: address of first character
*/

void _putstr(char *s)
{
	while (*s)
	{
		_putchar(*s);
		s++;
	}
}

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

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 * Return: 0
 */
int _strcmp(char *s1, char *s2)
{
	int i, diff;

	diff = 0;
	for (i = 0; (s1[i] != '\0' || s2[i] != '\0'); i++)
	{
		diff = s1[i] - s2[i];
		if (diff != 0)
			break;
	}


	return (diff);
}
