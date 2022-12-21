#include "main.h"

/**
 * ninteractive - non-interactive shell mode
 * @state: state struct containing all shared variables
 * @argv: argument vector from main
 * Return: 0 (success)
*/
int ninteractive(state_t *state, char **argv)
{
	pid_t pid;

	if (!argv[1])
	{
		getline(&state->command, &state->command_len, stdin);
		state->command = strcnl(state->command);
		make_args(state);
	}

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);

	if (pid == 0)
	{
		if (argv[1])
		{
			execve(argv[1], argv + 1, environ);
			state->args = argv + 1;
			handle_errors(state);
		}
		else
		{
			execve(state->args[0], state->args, environ);
			handle_errors(state);
		}
	}
	else
	{
		wait(NULL);
		free(state);
	}

	return (0);
}
