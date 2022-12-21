#include "main.h"

/**
 * interactive - interactive shell
 * @state: state struct of shell containing all shared variables
 * Return: 0 (success)
*/
int interactive(state_t *state)
{
	pid_t pid;

	while (1)
	{
		_printf("($) ");
		getline(&state->command, &state->command_len, stdin);
		state->command = strcnl(state->command);

		if (!_strcmp(state->command, ""))
			continue;
		if (!_strcmp(state->command, "exit"))
			return (0);

		if (!abs_path(state))
			validate(state);

		make_args(state);

		pid = fork();
		if (pid == -1)
			exit(EXIT_FAILURE);

		if (pid == 0)
		{
			execve(state->args[0], state->args, environ);
			exit(EXIT_FAILURE);
		}
		else
			wait(NULL);
	}

	return (1);
}
