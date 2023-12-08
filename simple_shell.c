#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
    // Display prompt and get user input
    prompt();
    if (fgets(line, MAX_LINE_LENGTH, stdin) == NULL) {
      printf("\n");
      break;  // Handle EOF
    }

    // Remove trailing newline
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
      continue;  // Skip empty commands
    }

    // Fork a child process to execute the command
    status = fork();
    if (status == 0) {
      // Child process
      execve(line, NULL, environ);
      perror("execve");  // Print error if execve fails
      exit(1);
    } else if (status > 0) {
      // Parent process
      wait(NULL);  // Wait for child process to finish
    } else {
      perror("fork");  // Print error if fork fails
    }
  }

  return 0;
}
