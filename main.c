#include "main.h"

/**
 * main - simple shell program
 * @argc: arguments' count
 * @argv: arguments' vector
 * Return: 0 (success)
*/
int main(int argc, char **argv)
{
	state_t state = {NULL, 1, NULL, {NULL}, {NULL}, NULL};

	if (argc > 1 || !isatty(STDIN_FILENO))
	{
		ninteractive(&state, argv);
		return (0);
	}

	interactive(&state);

	return (0);
}
