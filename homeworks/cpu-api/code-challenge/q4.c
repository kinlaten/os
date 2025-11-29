#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  if (pid == -1) {
    perror("Fork failed");
    return 1;
  }

  if (pid == 0) {
    char *args[10];
    args[0] = "/bin/ls";
    args[1] = "-l";
    args[2] = ".";
    args[3] = NULL;
    // execvp(args[0], args); // pass arguments as char* const []

    // args[0] = "ls"; //This make next line Failed: no p means it cannot refer
    // command dynamically
    execv(args[0], args);

    perror("execlp failed");
    exit(1);
  } else {
    int status;
    wait(&status);
    printf("Parent: Finished\n");
    execlp("ls", "ls", "-l", "/home",
           (char *)NULL); // pass arguments as const char*
  }

  return 0;
}
