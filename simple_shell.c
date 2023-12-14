#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

#define MAX_ARGS 100

void print_prompt(int interactive) {
    if (interactive) {
        char *dollar = "$";
        printf("%s ", dollar);
    }
}

int main(void) {
    int num_tokens, k;
    size_t i;
    char *args[MAX_ARGS];
    char *command = NULL;
    char *token;
    size_t buffer = 0;
    size_t length;
    char *path[] = {"/usr/local/bin/", "/usr/bin/", "/bin/", "/usr/local/games/", "/usr/games/"};
    char full_path[MAX_ARGS];
    int status;
    pid_t pid;
    char **env = environ;

    int interactive = isatty(fileno(stdin));

    	while (1) {
        print_prompt(interactive);
        if (getline(&command, &buffer, stdin) != -1) {
            length = strlen(command);
            if (command[length - 1] == '\n')
                command[length - 1] = '\0';

            if (strcmp(command, "") == 0)
                continue;

            if (strcmp(command, "exit") == 0) {
                free(command);
                return 0;
            }

            num_tokens = 0;
            token = strtok(command, " ");
            while (token != NULL && num_tokens < MAX_ARGS - 1) {
                args[num_tokens++] = token;
                token = strtok(NULL, " ");
            }
            args[num_tokens] = NULL;

            if (num_tokens == 0)
                continue;

            for (k = 0; k < num_tokens; k++)
                ;

            if (access(args[0], X_OK) == 0) {
                for (i = 0; i < 5; i++) {
                    execve(command, args, env);
                    break;
                }

            } else {
                for (i = 0; i < 5; i++) {
                    strcpy(full_path, path[i]);
                    strcat(full_path, args[0]);

                    if (access(full_path, X_OK) == 0)
                        break;
                }
            }

            if (access(full_path, X_OK) == -1) {
                printf("Command not found\n");
                continue;
            }
            pid = fork();
            if (pid == -1) {
                perror("fork failed");
                exit(EXIT_FAILURE);
            }

            if (pid == 0) {
                if (execve(full_path, args, env) == -1) {
                    printf("Command not found\n");
                    exit(EXIT_FAILURE);
                }
            } else {
                waitpid(pid, &status, 0);
            }
        } else {
            if (!interactive)
                break;
            printf("\n");
            break;
        }
    }
    free(command);
    return 0;
}
