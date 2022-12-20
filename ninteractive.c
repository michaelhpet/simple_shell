#include "main.h"

/**
 * ninteractive - non-interactive shell mode
 * @argv: argument vector from main
 * @env: environment vector from main
 * Return: 0 (success)
*/
int ninteractive(char **argv, char **env)
{
	size_t command_len;
	char *command, *arg, *args[1024];
	pid_t pid;

	if (!argv[1])
	{
		getline(&command, &command_len, stdin);
		command = strcnl(command);
		make_args(command, arg, args);
	}

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);

	if (pid == 0)
	{
		if (argv[1])
		{
			execve(argv[1], argv + 1, env);
			handle_errors(argv + 1);
		}
		else
		{
			execve(args[0], args, env);
			handle_errors(args);
		}
	}
	else
		wait(NULL);

	return (0);
}
