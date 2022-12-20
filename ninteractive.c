#include "main.h"

/**
 * ninteractive - non-interactive shell mode
 * @argv: argument vector from main
 * @env: environment vector from main
 * Return: 0 (success)
*/
int ninteractive(char **argv, char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);

	if (pid == 0)
		execve(argv[1], argv + 1, env);
	else
		wait(NULL);

	return (0);
}
