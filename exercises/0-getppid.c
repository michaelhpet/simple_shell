#include <stdio.h>
#include <unistd.h>

/**
 * main - prints the PID of the parent process
 * Return: 0 (success)
*/
int main(void)
{
	int ppid;

	ppid = getppid();
	printf("Parent PID: %d\n", ppid);

	return (0);
}
