
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char message[100];

  int rc = fork(); // create child1

  if (rc > 0) {
    strcpy(message, "Goodbye");
    printf("%s\n", message);
  } else if (rc == 0) {
    wait(NULL); // child is parent to no one so wait() exit immediately

    strcpy(message, "Hello");
    printf("%s\n", message);
  } else {
    exit(1);
  }

  return 0;
}
