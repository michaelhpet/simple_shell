#include "main.h"

/**
 * _strcat - concatenates two strings
 * @dest: string to concat into
 * @src: string to concat from
 * Return: pointer to resulting string dest
 */

char *_strcat(char *dest, char *src)
{
	int i, len_dest, len_src;

	len_dest = 0;
	while (dest[len_dest] != '\0')
		len_dest++;

	len_src = 0;
	while (src[len_src] != '\0')
		len_src++;

	for (i = 0; i <= len_src; i++)
		dest[i + len_dest] = src[i];

	return (dest);
}

/**
 * print_char - prints a char using a va_list
 * @args: variadic args list
 * Return: length of char printed
*/
int print_char(va_list args)
{
	_putchar(va_arg(args, int));

	return (1);
}

/**
 * print_str - prints a string using a va_list
 * @args: variadic args list
 * Return: number of characters printed
*/
int print_str(va_list args)
{
	int len;
	char *str;

	str = va_arg(args, char *);

	if (str == NULL)
	{
		_putstr("(null)");
		return (6);
	}

	len = _strlen(str);
	if (*str)
		_putstr(str);

	return (len);
}
