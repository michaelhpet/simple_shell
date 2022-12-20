#include "main.h"

/**
 * main - simple shell program
 * @argc: arguments' count
 * @argv: arguments' vector
 * @env: enviromnent variables vector
 * Return: 0 (success)
*/
int main(int argc, char **argv, char **env)
{
	if (argc > 1 || !isatty(STDIN_FILENO))
	{
		ninteractive(argv, env);
		return (0);
	}

	interactive(env);

	return (0);
}
