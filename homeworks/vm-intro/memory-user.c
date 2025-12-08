#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    perror("Error: please enter ./program memory runTime");
    return 1;
  }

  int memory = atoi(argv[1]) * 1024 * 1024;
  int length = (int)(memory / sizeof(int));
  int *arr = malloc(memory);

  int runTime = atoi(argv[2]);
  clock_t begin = clock();

  while (1) {
    int timeSpent = (clock() - begin) / CLOCKS_PER_SEC;
    if (timeSpent >= runTime) {
      break;
    }
    for (int i = 0; i < length; i++) {
      printf("%ds\n", i);
      arr[i]++;
    }
  }
  free(arr);
  return 0;
}
