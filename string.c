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
