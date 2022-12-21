#include "main.h"

/**
 * _printenv - prints the current environment
 * @state: state struct containing all shared variables
 * Return: 0
 */
int _printenv(state_t *state)
{
	print_list_str(state->env);
	return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @state: state struct containing all shared variables
 * @key: environmant variable key string
 * Return: environment variable value string
 */
char *_getenv(state_t *state, const char *key)
{
	list_t *node = state->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, key);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _initenv - initialize an environment variable
 * @state: state struct containing all shared variables
 * Return: 0
 */
int _initenv(state_t *state)
{
	if (state->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(state, state->argv[1], state->argv[2]))
		return (0);
	return (1);
}

/**
 * _vunsetenv - Remove an environment variable
 * @state: state struct containing all shared variables
 * Return: 0
 */
int _vunsetenv(state_t *state)
{
	int i;

	if (state->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= state->argc; i++)
		_unsetenv(state, state->argv[i]);

	return (0);
}

/**
 * make_envs - populates env linked list
 * @state: state struct containing all shared variables
 * Return: 0
 */
int make_envs(state_t *state)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	state->env = node;
	return (0);
}
