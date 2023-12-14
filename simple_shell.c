#include "shell.h"
#include <stdio.h>

char **parse_command(char *line);

void exit_shell() {
    printf("Exiting shell.\n");
    exit(EXIT_SUCCESS);
}

int main(void) {
    char line[MAX_LINE_LENGTH];
    char **args;
    char *copied_file;
    pid_t pid;

    while (1) {
        /* Display prompt */
        printf(":) ");

        /* Read user input */
        if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) {
            /* Handle end of file (Ctrl+D) */
            printf("\n");
            break;
        }

        line[strcspn(line, "\n")] = '\0'; /* Remove trailing newline */

        if (line[0] == '\0' || line[0] == ' ') {
            /* Case: Empty or spaces-only line */
            continue;
        }

        /* Parse command */
        args = parse_command(line);

        /* Check for exit command */
        if (!strcmp(args[0], "exit")) {
            free(args);
            break;
        }
	
	/* Handle special case: copy and execute */
	if (!strcmp(args[0], "cp")) {
    	pid_t cp_pid;

    	if (args[1] == NULL || args[2] == NULL) {
        fprintf(stderr, "Invalid cp command.\n");
        free(args);
        continue;
    }

    /* Copy the file using cp */
    cp_pid = fork();
    if (cp_pid == 0) {
        execlp("cp", "cp", args[1], args[2], (char *)NULL);
        perror("cp");
        exit(EXIT_FAILURE);
    }
    waitpid(cp_pid, NULL, 0);

    /* Extract copied filename and remaining arguments */
    copied_file = strdup(args[2]);
    args[0] = copied_file;
}

        /* Fork a child process */
        pid = fork();

        if (pid == 0) { /* Child process */
            /* Execute command with arguments */
            execvp(args[0], args);
            perror(args[0]);
            free(args[0]);
            free(args);
            exit(EXIT_FAILURE);
        } else if (pid == -1) { /* Error */
            perror("fork");
            free(args);
            exit(EXIT_FAILURE);
        } else { /* Parent process */
            waitpid(pid, NULL, 0); /* Wait for child to finish */
            free(args[0]);
            free(args);
        }
    }

    return 0;
}

/* Implementation of parse_command function */
char **parse_command(char *line) {
    int buffer_size = MAX_LINE_LENGTH;
    int position = 0;
    char **tokens = malloc(buffer_size * sizeof(char *));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Allocation error\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, " ");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= buffer_size) {
            buffer_size += MAX_LINE_LENGTH;
            tokens = realloc(tokens, buffer_size * sizeof(char *));
            if (!tokens) {
                fprintf(stderr, "Allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, " ");
    }
    tokens[position] = NULL;
    return tokens;
}
