#include "main.h"

/**
 * interactive - interactive shell
 * @env: environment vector from main
 * Return: 0 (success)
*/
int interactive(char **envp)
{
	pid_t pid;
	int wstat;
	size_t command_len;
	char *command, *arg, *args[1024];

	do {
		printf("$ ");
		command_len = 1;
		getline(&command, &command_len, stdin);
		command = strcnl(command);

		if (!_strcmp(command, ""))
			continue;
		if (!_strcmp(command, "exit"))
			break;

		make_args(command, arg, args);

		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);

		if (pid == 0)
		{
			execve(args[0], args, envp);
			handle_errors(args);
			break;
		}
		else
			wait(&wstat);
	} while (1);

	return (0);
}
