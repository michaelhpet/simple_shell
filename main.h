#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

/**
 * struct format - format specifier
 * @specifier: char specifying format
 * @printer: function to print arg for specifier
*/
struct format
{
	char specifier;
	int (*printer)(va_list args);
};

/**
 * format_t - type definition for format
*/
typedef struct format format_t;

int _printf(const char *format, ...);
int _vprintf(const char *format, va_list args);
int _putchar(char c);
void _putstr(char *c);
int _strlen(char *s);
int printer(char format, va_list args);
int print_char(va_list args);
int print_str(va_list args);
int is_specifier(char ch);
int print_int(va_list args);
int count_digits(unsigned int number);
int _pow(int base, int exp);

/**
 * struct _state - a struct holding all the state values of the shell
 * shared by all functions
 * @command: command string
 * @command_len: minimum length of command string
 * @arg: first token of command used as args[0]
 * @args: args vector in execve-usable format
 * @paths: PATHs in array of strings format
 * @path_dir: current dir string of program to run if in paths
*/
struct _state
{
	char *command;
	size_t command_len;
	char *arg;
	char *args[1024];
	char *paths[1024];
	char *path_dir;
};

/**
 * state_t - type definition for state struct
*/
typedef struct _state state_t;

extern char **environ;

int _strcmp(char *s1, char *s2);
char *strcnl(char *str);
char *_strcat(char *dest, char *src);

state_t *init_state(state_t **state);
void free_state(state_t *state);

void make_args(state_t *state);
int ninteractive(state_t *state, char **argv);
int interactive(state_t *state);
void handle_errors(state_t *state);
void validate(state_t *state);
int is_builtin(state_t *state);
int in_path(state_t *state);
int run_builtin(state_t *state);
void get_paths(state_t *state);
int abs_path(state_t *state);

#endif /* _MAIN_H_ */
