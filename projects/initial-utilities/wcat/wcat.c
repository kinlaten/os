#include <stdio.h>

// With FILE, no tag
int print_file(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("wcat: cannot open file\n");
    return 1;
  }

  char ch;
  while ((ch = fgetc(file)) != EOF) {
    // plush stream to stdout from buffer
    putchar(ch);
  }

  fclose(file);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    return 0;
  }

  for (int i = 1; i < argc; i++) {
    if (print_file(argv[i]) == 1) {
      return 1;
    }
  }

  return 0;
}
