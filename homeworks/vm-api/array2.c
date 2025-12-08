#include <stdio.h>
#include <stdlib.h>
// problem 6
int main() {
  int *arr = malloc(100 * sizeof(int));
  arr[1] = 15;

  printf("%p\n", arr);
  free(arr);

  printf("%d\n", arr[1]);

  return 0;
}
