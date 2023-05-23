# Simple Shell

A simple UNIX command line interpreter

Implementation reference:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char line[1024];
  char *command;
  char *args[1024];
  int i;

  while (1) {
    printf("myshell> ");
    fflush(stdout);

    fgets(line, sizeof(line), stdin);
    line[strlen(line) - 1] = '\0';

    command = strtok(line, " ");

    if (command == NULL) {
      continue;
    }

    args[0] = command;
    i = 1;

    while (1) {
      command = strtok(NULL, " ");

      if (command == NULL) {
        break;
      }

      args[i++] = command;
    }

    execvp(args[0], args);

    perror("execvp");
    exit(1);
  }

  return 0;
}

```
