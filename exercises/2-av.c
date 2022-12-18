#include <stdio.h>

/**
 * main - prints all arguments without using ac
 * @ac: arguments' count
 * @av: arguments' vector
 * Return: 0 (success)
*/
int main(int __attribute__((__unused__))ac, char *av[])
{
	int i;

	i = 0;
	while (av[i])
	{
		printf("%s\n", av[i]);
		i++;
	}

	return (0);
}
