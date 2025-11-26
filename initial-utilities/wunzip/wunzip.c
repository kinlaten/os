#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("wunzip: file1 [file2 ...]\n");
    return 1;
  }

  // Process all files as a single continuous stream
  for (int i = 1; i < argc; i++) {
    FILE *input = fopen(argv[i], "rb");
    if (input == NULL) {
      printf("wunzip: cannot open file %s\n", argv[i]);
      return 1;
    }

    int count;
    char c;

    while (fread(&count, sizeof(int), 1, input) == 1) {
      if (fread(&c, sizeof(char), 1, input) == 1) {
        for (int j = 0; j < count; j++) {
          printf("%c", c);
        }
      } else {
        break;
      }
    }

    fclose(input);
  }

  return 0;
}