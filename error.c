#include "main.h"

/**
 * handle_error - handle various shell errors
 * @command: command vector passed to exec
*/
void handle_errors(char **command)
{
	_printf("hsh: command not found: %s\n", command[0]);
}
