#include "main.h"

/**
 * shell - main shell loop
 * @state: the parameter & return state struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int shell(state_t *state, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		reset_state(state);
		if (interactive(state))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(state);
		if (r != -1)
		{
			init_state(state, av);
			builtin_ret = find_builtin(state);
			if (builtin_ret == -1)
				find_cmd(state);
		}
		else if (interactive(state))
			_putchar('\n');
		free_state(state, 0);
	}
	write_history(state);
	free_state(state, 1);
	if (!interactive(state) && state->status)
		exit(state->status);
	if (builtin_ret == -2)
	{
		if (state->err_num == -1)
			exit(state->status);
		exit(state->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @state: the parameter & return state struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(state_t *state)
{
	int i, built_in_ret = -1;
	builtin_t builtintbl[] = {
		{"exit", _myexit},
		{"env", _printenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _initenv},
		{"unsetenv", _vunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(state->argv[0], builtintbl[i].type) == 0)
		{
			state->line_count++;
			built_in_ret = builtintbl[i].func(state);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @state: the parameter & return state struct
 *
 * Return: void
 */
void find_cmd(state_t *state)
{
	char *path = NULL;
	int i, k;

	state->path = state->argv[0];
	if (state->linecount_flag == 1)
	{
		state->line_count++;
		state->linecount_flag = 0;
	}
	for (i = 0, k = 0; state->arg[i]; i++)
		if (!is_delim(state->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(state, _getenv(state, "PATH="), state->argv[0]);
	if (path)
	{
		state->path = path;
		fork_cmd(state);
	}
	else
	{
		if ((interactive(state) || _getenv(state, "PATH=")
			|| state->argv[0][0] == '/') && is_cmd(state, state->argv[0]))
			fork_cmd(state);
		else if (*(state->arg) != '\n')
		{
			state->status = 127;
			print_error(state, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @state: the parameter & return state struct
 *
 * Return: void
 */
void fork_cmd(state_t *state)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(state->path, state->argv, _getenvs(state)) == -1)
		{
			free_state(state, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(state->status));
		if (WIFEXITED(state->status))
		{
			state->status = WEXITSTATUS(state->status);
			if (state->status == 126)
				print_error(state, "Permission denied\n");
		}
	}
}

/**
 * input_buf - buffers chained commands
 * @state: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(state_t *state, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)state->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(state, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			state->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(state, *buf, state->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				state->cmd_buf = buf;
			}
		}
	}
	return (r);
}
