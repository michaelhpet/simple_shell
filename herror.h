#ifndef _HERROR_H_
#define _HERROR_H_

int _erratoi(char *);
void print_error(state_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

#endif
