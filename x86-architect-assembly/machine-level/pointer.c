#include <stdio.h>

int main() {
  int x = 10; // Standard variable
  printf("x is at %p\n", &x);
  int *p = &x; // Pointer pointing to x

  *p = 20; // Using the pointer to change x

  return x; // Return x so we can see the final value
}
