#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int x;
  x = 100;
  printf("Parent init x = %d\n", x);

  int rc = fork();

  // in the if statement, actually child and parent have same initial input
  // x=100 but then their next assignment on x independent from each other
  if (rc > 0) {
    wait(NULL);
    printf("Parent have x = %d\n", x);
    x = 200;
    printf("Parent change x = %d\n", x);
  } else if (rc == 0) {
    printf("Child has x = %d\n", x);
    x = 50;
    printf("Child changes x = %d\n", x);
  } else {
    x = 0;
    exit(1);
  }

  printf("Finally x = %d\n", x);
  printf("\n");
  return 0;
}
