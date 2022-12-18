#include "main.h"

/**
 * main - simple shell program
 * Return: 0 (success)
*/
int main(void)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
		return (1);

	if (pid == 0)
		_shell();
	else
		wait(NULL);

	return (0);
}

/**
 * _shell - a shell function
 * Return: 0 (success)
*/
int _shell(void)
{
	char *buffer, *exit_command;
	size_t buffer_size;

	buffer_size = 1024;
	buffer = malloc(sizeof(char) * buffer_size);
	if (buffer == NULL)
		exit(98);

	exit_command = "exit\n";
	while (_strcmp(buffer, exit_command))
	{
		printf("->  ");
		getline(&buffer, &buffer_size, stdin);
		printf("%s", buffer);
	}

	free(buffer);

	return (0);
}
