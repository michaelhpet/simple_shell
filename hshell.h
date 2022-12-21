#ifndef _HSHELL_H_
#define _HSHELL_H_

int shell(state_t *, char **);
int find_builtin(state_t *);
void find_cmd(state_t *);
void fork_cmd(state_t *);
int is_cmd(state_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(state_t *, char *, char *);
int loophsh(char **);
ssize_t get_input(state_t *);
int _getline(state_t *, char **, size_t *);
ssize_t input_buf(state_t *state, char **buf, size_t *len);
void sigintHandler(int);

void reset_state(state_t *);
void init_state(state_t *, char **);
void free_state(state_t *, int);

char *_getenv(state_t *, const char *);
int _printenv(state_t *);
int _initenv(state_t *);
int _vunsetenv(state_t *);
int make_envs(state_t *);

char **_getenvs(state_t *);
int _unsetenv(state_t *, char *);
int _setenv(state_t *, char *, char *);

char *get_history_file(state_t *state);
int write_history(state_t *state);
int read_history(state_t *state);
int build_history_list(state_t *state, char *buf, int linecount);
int renumber_history(state_t *state);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

int is_chain(state_t *, char *, size_t *);
void check_chain(state_t *, char *, size_t *, size_t, size_t);
int replace_alias(state_t *);
int replace_vars(state_t *);
int replace_string(char **, char *);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);


char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);

#endif
