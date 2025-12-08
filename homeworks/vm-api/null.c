#include <stdio.h>

int main() {
  int *ptr = NULL; // Address 0x0 is reserved for nullptr only, we cannot
                   // operate writing or reading here.
  int result = *ptr;
  printf("%d", result);
  return 0;
}
