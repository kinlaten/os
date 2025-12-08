#include <stdio.h>
#include <stdlib.h>
// problem 5
int main() {
  int *arr = malloc(100 * sizeof(int));
  arr[100] = 0; // out of bound error

  free(arr); // If not specify, Leak memory occurs
             // 'definitely lost: 400 bytes in 1 blocks'

  return 0;
}
