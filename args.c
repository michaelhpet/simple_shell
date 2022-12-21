#include "main.h"

/**
 * make_args - creates an array of string args from strtok yields
 * @state: state struct containing all shared variabled
*/
void make_args(state_t *state)
{
	int i;

	i = 0;
	state->arg = strtok(state->command, " ");
	while (state->arg)
	{
		state->args[i++] = state->arg;
		state->arg = strtok(NULL, " ");
	}
	state->args[i] = NULL;
}

/**
 * abs_path - checks if program file is absolute path
 * @state: state struct containing all shared variables
 * Return: 1 if absolute, 0 otherwise
*/
int abs_path(state_t *state)
{
	if (state->command[0] == '/')
		return (1);

	return (0);
}
