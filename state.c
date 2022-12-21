#include "main.h"

/**
 * reset_state - initializes state_t struct
 * @state: struct address
 */
void reset_state(state_t *state)
{
	state->arg = NULL;
	state->argv = NULL;
	state->path = NULL;
	state->argc = 0;
}

/**
 * init_state - initializes state_t struct
 * @state: struct address
 * @av: argument vector
 */
void init_state(state_t *state, char **av)
{
	int i = 0;

	state->fname = av[0];
	if (state->arg)
	{
		state->argv = strtow(state->arg, " \t");
		if (!state->argv)
		{

			state->argv = malloc(sizeof(char *) * 2);
			if (state->argv)
			{
				state->argv[0] = _strdup(state->arg);
				state->argv[1] = NULL;
			}
		}
		for (i = 0; state->argv && state->argv[i]; i++)
			;
		state->argc = i;

		replace_alias(state);
		replace_vars(state);
	}
}

/**
 * free_state - frees state_t struct fields
 * @state: struct address
 * @all: true if freeing all fields
 */
void free_state(state_t *state, int all)
{
	ffree(state->argv);
	state->argv = NULL;
	state->path = NULL;
	if (all)
	{
		if (!state->cmd_buf)
			free(state->arg);
		if (state->env)
			free_list(&(state->env));
		if (state->history)
			free_list(&(state->history));
		if (state->alias)
			free_list(&(state->alias));
		ffree(state->environ);
			state->environ = NULL;
		bfree((void **)state->cmd_buf);
		if (state->readfd > 2)
			close(state->readfd);
		_putchar(BUF_FLUSH);
	}
}
