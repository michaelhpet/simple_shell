#include "main.h"

/**
 * validate - validates a shell command by checking built-ins
 * and environmant namespace
 * @state: shell state struct containing all shared variables
*/
void validate(state_t *state)
{
	char *path;

	if (is_builtin(state))
		run_builtin(state);
	else if (in_path(state))
	{
		path = malloc(sizeof(char) * 1024);
		if (path == NULL)
		{
			free_state(state);
			exit(EXIT_FAILURE);
		}
		path[0] = 0;
		path = strcat(path, state->path_dir);
		path = strcat(path, "/");
		path = strcat(path, state->command);
		free(state->command);
		state->command = path;
	}
	else
		handle_errors(state);
}

/**
 * is_builtin - checks if a command is built-in
 * @state: state struct of shell containing all shared variables
 * Return: 1 if built-in, 0 otherwise
*/
int is_builtin(state_t *state)
{
	int i;
	char *builtin[] = {"pwd", "env", NULL};

	i = 0;
	while (builtin[i])
	{
		if (_strcmp(state->command, builtin[i++]) == 0)
			return (1);
	}

	return (0);
}

/**
 * in_path - checks if a command is available in env PATH
 * @state: state struct of shell containing all shared variables
 * Return: 1 if in PATH, 0 otherwise
*/
int in_path(state_t *state)
{
	int i;
	DIR *dir;
	struct dirent *ent;

	get_paths(state);

	i = 0;
	while (state->paths[i])
	{
		dir = opendir(state->paths[i]);
		if (dir)
		{
			ent = readdir(dir);
			while (ent)
			{
			if (_strcmp(ent->d_name, ".") && _strcmp(ent->d_name, ".."))
			{
			if (_strcmp(ent->d_name, state->command) == 0)
			{
				free(state->path_dir);
				state->path_dir = state->paths[i];
				return (1);
			}
			}
			ent = readdir(dir);
			}
		}
		closedir(dir);
		i++;
	}

	return (0);
}

/**
 * get_paths - get array of PATH variables
 * @state: state struct of shell containing all shared variables
 * Return: pointer to array of path strings
*/
void get_paths(state_t *state)
{
	int i, j;
	char *key, *value, *path;

	i = 0, j = 0;
	while (environ[i])
	{
		key = strtok(environ[i++], "=");
		value = strtok(NULL, "=");
		if (_strcmp(key, "PATH") == 0)
		{
			path = strtok(value, ":");
			j = 0;
			while (path)
			{
				state->paths[j++] = path;
				path = strtok(NULL, ":");
			}
		}
	}
	state->paths[j] = NULL;
}


/**
 * run_builtin - runs a builtin command
 * @state: state struct of shell containing shared variables
 * Return: 0 (success)
*/
int run_builtin(state_t *state)
{
	char *buff;

	buff = getcwd(NULL, 1024);
	_printf("%s, %s\n", state->args[0], buff);
	free(buff);

	return (0);
}
