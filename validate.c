#include "main.h"

/**
 * validate - validates a shell command by checking built-ins
 * and environmant namespace
 * @command: parsed command in execve-usable array
*/
void validate(char *args[], char **envp)
{
	if (is_builtin(args[0]))
		run_builtin(args, envp);

	if (!in_path(args[0], envp))
		handle_errors(args);
}

/**
 * is_builtin - checks if a command is built-in
 * @command: command string
 * Return: 1 if built-in, 0 otherwise
*/
int is_builtin(char *command)
{
	int i;
	char *builtin[] = {"pwd", NULL};

	i = 0;
	while (builtin[i])
	{
		if (_strcmp(command, builtin[i++]) == 0)
			return (1);
	}

	return (0);
}

/**
 * in_path - checks if a command is available in env PATH
 * @command: command string
 * Return: 1 if in PATH, 0 otherwise
*/
int in_path(char *command, char **envp)
{
	int i, j, diff;
	char *path;

	i = 0;
	diff = 0;
	while (envp[i++])
	{
		j = 0;
		while (envp[i][j++] || command != "=")
		{
			diff = envp[i][j] - command[j];
			if (diff != 0)
				break;
		}
	}

	return (1);
}

/**
 * run_builtin - runs a builtin command
 * @args: argument vector
 * Return: 0 (success)
*/
int run_builtin(char *args[], char **envp)
{
	char *buff;

	buff = getcwd(NULL, 1024);
	_printf("%s\n", buff);
	free(buff);

	return (0);
}
