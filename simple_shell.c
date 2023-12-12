#include "shell.h"

int main(void)
{
  char line[MAX_LINE_LENGTH];
  char **args;
  char *copied_file;
  char **parse_command(char *line);

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

    line[strcspn(line, "\n")] = '\0'; /* Remove trailing newline */

    if (!strcmp(line, "")) { /* Case: Spaces only (small/large/medium) */
      continue;
    }

    /* Split the line into arguments */;

    /* Check for exit command */
    if (!strcmp(args[0], "exit")) {
      break;
    }

    /* Handle special case: copy and execute */
    if (!strcmp(args[0], "cp")) {
      int ret = system(line); /* Copy using system() */
      if (ret != 0) {
        perror("system");
        continue;
      }
      /* Extract copied filename and remaining arguments */
      copied_file = strtok(line + 3, " ");
      args = &copied_file; /* Use remaining args for execve */
    }

    /* Fork a child process */
    pid = fork();

    if (pid == 0) /* Child process */
    {
      /* Execute command with arguments */
      execvp(args[0], args);
      perror(args[0]);
      exit(1);
    }
      else if (pid == -1) /* Error */
    {
      perror("fork");
      exit(1);
    }
      else /* Parent process */
    {
      waitpid(pid, NULL, 0); /* Wait for child to finish */
    }
  }

  return 0;
}
