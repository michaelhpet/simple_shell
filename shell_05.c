#include "main.h"

/**
 * get_history_file - gets the history file
 * @state: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(state_t *state)
{
	char *buf, *dir;

	dir = _getenv(state, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file, or appends to an existing file
 * @state: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(state_t *state)
{
	ssize_t fd;
	char *filename = get_history_file(state);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = state->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history from file
 * @state: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(state_t *state)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(state);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(state, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(state, buf + last, linecount++);
	free(buf);
	state->histcount = linecount;
	while (state->histcount-- >= HIST_MAX)
		delete_node_at_index(&(state->history), 0);
	renumber_history(state);
	return (state->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @state: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: 0
 */
int build_history_list(state_t *state, char *buf, int linecount)
{
	list_t *node = NULL;

	if (state->history)
		node = state->history;
	add_node_end(&node, buf, linecount);

	if (!state->history)
		state->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @state: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(state_t *state)
{
	list_t *node = state->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (state->histcount = i);
}
