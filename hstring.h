#ifndef _HSTRING_H_
#define _HSTRING_H_

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);
char **strtow(char *, char *);
char **strtow2(char *, char);
int interactive(state_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

#endif
