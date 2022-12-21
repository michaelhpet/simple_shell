#include "main.h"

/**
 * unset_alias - sets alias to string
 * @state: parameter struct
 * @str: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(state_t *state, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(state->alias),
		get_node_index(state->alias, node_starts_with(state->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @state: parameter struct
 * @str: the string alias
 *
 * Return: 0 on success, 1 on error
 */
int set_alias(state_t *state, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(state, str));

	unset_alias(state, str);
	return (add_node_end(&(state->alias), str, 0) == NULL);
}
