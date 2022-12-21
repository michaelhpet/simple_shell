#include "main.h"

/**
 * handle_errors - handle various shell errors
 * @state: state struct of shell containing all shared variables
*/
void handle_errors(state_t *state)
{
	_printf("hsh: command not found: %s\n", state->args[0]);
}
