#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int _shell(void);
int _strcmp(char *s1, char *s2);
void make_args(char *command, char *arg, char **args);
char *strcnl(char *str);
int ninteractive(char **argv, char **env);
int interactive(char **env);

#endif /* _MAIN_H_ */
