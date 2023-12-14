#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
#define MAX_LINE_LENGTH 256

/* prototype */
int mul(int a, int b);
int main(void);
char *read_line(void);
char **parse_command(char *line);
int execute_command(char **args);
char **parse_command(char *line);

/* Variable prototypes */
extern char **environ;

#endif
