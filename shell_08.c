#include "main.h"

/**
 * _getenvs - get environment variables
 * @state: state struct containing all shared variables
 * Return: environment variables in string array format
 */
char **_getenvs(state_t *state)
{
	if (!state->environ || state->env_changed)
	{
		state->environ = list_to_strings(state->env);
		state->env_changed = 0;
	}

	return (state->environ);
}

/**
 * _unsetenv - unset an environment variable
 * @state: state struct containing all shared variables
 * @key: environmant variable key string
 * Return: 1 on success, 0 otherwise
 */
int _unsetenv(state_t *state, char *key)
{
	list_t *node = state->env;
	size_t i = 0;
	char *p;

	if (!node || !key)
		return (0);

	while (node)
	{
		p = starts_with(node->str, key);
		if (p && *p == '=')
		{
			state->env_changed = delete_node_at_index(&(state->env), i);
			i = 0;
			node = state->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (state->env_changed);
}

/**
 * _setenv - initialize an environment variable
 * @state: state struct containing all shared variables
 * @key: environmant variable key string
 * @value: environment variable value string
 * Return: 0
 */
int _setenv(state_t *state, char *key, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!key || !value)
		return (0);

	buf = malloc(_strlen(key) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, key);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = state->env;
	while (node)
	{
		p = starts_with(node->str, key);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			state->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(state->env), buf, 0);
	free(buf);
	state->env_changed = 1;
	return (0);
}
