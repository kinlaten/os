#include <stdio.h>
#include <stdlib.h>
// problem 6
int main() {
  int *arr = malloc(100 * sizeof(int));
  printf("Address: %p\n", arr);
  free(arr + 4);
  return 0;
}
