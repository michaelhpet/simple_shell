#ifndef _STRUCTS_H_
#define _STRUCTS_H_

/**
 * struct list - singly linked list of string values
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
struct list
{
	int num;
	char *str;
	struct list *next;
};

/*
 * list_t - type definition for struct list
*/
typedef struct list list_t;



/**
 * struct state - struct containing all shared variables
 * @arg: a string generated from getline containing arguements
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
struct state
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
};

/*
 * state_t - type definition for struct state
*/
typedef struct state state_t;

/**
 * struct builtin - builtin string command with associated function
 * @type: builtin command string
 * @func: handler function
 */
struct builtin
{
	char *type;
	int (*func)(state_t *);
};

/*
 * builtin_t - type definition for struct builtin
*/
typedef struct builtin builtin_t;

#endif
