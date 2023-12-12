#include "shell.h"

int main(void) 
{
  char line[MAX_LINE_LENGTH];
  char *command;
  extern char **environ;

  pid_t pid;

  while (1) 
{
    /* Display prompt */
    printf("> ");

    /* Read user input */
    if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) 
	{
      /* Handle end of file (Ctrl+D) */
      printf("\n");
      break;
	}

    /* Extract command */
    line[strcspn(line, "\n")] = '\0';
    command = strtok(line, " ");

    /* Check if command is empty */
    if (command == NULL) 
	{
      continue;
	}

    /* Check if executable exists */
    if (access(command, X_OK) == -1) 
	{
      printf("'%s': command not found\n", command);
      continue;
	}

    /* Fork a child process */
    pid = 0;

    if (pid == -1)
	{
      perror("fork");
      exit(1);
	}

    /* Child process */
    if (pid == 0)
	{
      /* Execute command */
      execve(command, environ, NULL);
      perror("execve");
      exit(1);
	}

    /* Parent process*/
    waitpid(pid, NULL, 0);
}

  return 0;
}
