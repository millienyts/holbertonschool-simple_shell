#include "main.h"

#define MAX_LINE_LENGTH 128

/**
 * Displays the prompt for user input.
 */
void prompt() {
  printf("%s", "> ");
}

/**
 * Main function of the simple shell.
 */
int main(void) {
  char line[MAX_LINE_LENGTH];
  int status;

  while (1) {
    
    prompt();
    if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) {
      printf("\n");
      break;
    }


    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
      continue;
    }


    status = fork();
    if (status == 0) {

      execve(line, NULL, environ);
      perror("execve");
      exit(1);
    } else if (status > 0) {

      wait(NULL);
    } else {
      perror("fork");
    }
  }

  return 0;
}
