#include <stdio.h>

int main() {
  int x = 10;  // Standard variable
  int *p = &x; // Pointer pointing to x

  *p = 20; // Using the pointer to change x

  return x; // Return x so we can see the final value
}
