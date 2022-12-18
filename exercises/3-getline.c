#include <stdio.h>
#include <stdlib.h>

/**
 * main - prints user's input
 * Return: 0 (success)
*/
int main(void)
{
	char *buffer;
	size_t buffer_size;

	buffer_size = 1024;
	buffer = malloc(sizeof(char) * buffer_size);
	if (!buffer)
		return (1);

	printf("$ ");
	getline(&buffer, &buffer_size, stdin);

	printf("%s", buffer);

	return (0);
}
