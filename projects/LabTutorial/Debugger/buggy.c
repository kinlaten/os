#include <stdio.h>
struct Data {
  int x;
};
int main(int argc, char *argv[]) {
  struct Data *p = NULL;
  printf("%d\n", p->x);
}

// compile exe file then use gdb to debug: gdb buggy / run / break main / run /
// next / print p / next
