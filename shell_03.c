#include "main.h"

/**
 * _mycd - changes the current directory of the process
 * @state: state struct containing all shared variables
 * Return: 0
 */
int _mycd(state_t *state)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!state->argv[1])
	{
		dir = _getenv(state, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(state, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(state->argv[1], "-") == 0)
	{
		if (!_getenv(state, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(state, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(state, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(state->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(state, "can't cd to ");
		_eputs(state->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(state, "OLDPWD", _getenv(state, "PWD="));
		_setenv(state, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - changes the current directory of the process
 * @state: state struct containing all shared variables
 * Return: 0
 */
int _myhelp(state_t *state)
{
	char **arg_array;

	arg_array = state->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @state: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: 0
 */
int _myhistory(state_t *state)
{
	print_list(state->history);
	return (0);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @state: state struct containing all shared variables
 * Return: 0
 */
int _myalias(state_t *state)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (state->argc == 1)
	{
		node = state->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; state->argv[i]; i++)
	{
		p = _strchr(state->argv[i], '=');
		if (p)
			set_alias(state, state->argv[i]);
		else
			print_alias(node_starts_with(state->alias, state->argv[i], '='));
	}

	return (0);
}
