#include "main.h"

/**
 * main - simple shell program
 * @argc: arguments' count
 * @argv: arguments' vector
 * @env: enviromnent variables vector
 * Return: 0 (success)
*/
int main(int argc, char **argv, char **envp)
{
	if (argc > 1 || !isatty(STDIN_FILENO))
	{
		ninteractive(argv, envp);
		return (0);
	}

	interactive(envp);

	return (0);
}
