#include "main.h"

/**
 * init_state - initialize state struct storing all shared variables
 * @state: address of state struct
 * Return: state struct
*/
state_t *init_state(state_t **state)
{
	state_t *tmp;

	tmp = malloc(sizeof(tmp));
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	tmp->command = malloc(sizeof(char) * 1024);
	if (tmp->command == NULL)
	{
		free(tmp);
		exit(EXIT_FAILURE);
	}
	tmp->path_dir = malloc(sizeof(char) * 1024);
	if (tmp->path_dir == NULL)
	{
		free(tmp->command);
		free(tmp);
		exit(EXIT_FAILURE);
	}
	tmp->args = malloc(sizeof(char *) * 1024);
	if (tmp->args == NULL)
	{
		free(tmp->path_dir);
		free(tmp->command);
		free(tmp);
		exit(EXIT_FAILURE);
	}
	tmp->paths = malloc(sizeof(char *) * 1024);
	if (tmp->paths == NULL)
	{
		free(tmp->args);
		free(tmp->path_dir);
		free(tmp->command);
		free(tmp);
		exit(EXIT_FAILURE);
	}
	tmp->command[0] = 0,  tmp->path_dir[0] = 0;

	*state = tmp;

	return (*state);
}

/**
 * free_state - frees the state struct
 * @state: state struct containing all shared variables
*/
void free_state(state_t *state)
{
	free(state->paths);
	free(state->args);
	free(state->command);
	free(state);
}
