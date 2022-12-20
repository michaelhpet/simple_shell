#include "main.h"

/**
 * make_args - creates an array of string args from strtok yields
 * @command: command string to parse
 * @arg: pointer to store each argument token
 * @args: pointer to store array of argument tokens
*/
void make_args(char *command, char *arg, char **args)
{
	int i;

	i = 0;
	arg = strtok(command, " ");
	while (arg)
	{
		args[i++] = arg;
		arg = strtok(NULL, " ");
	}
	args[i] = NULL;
}
