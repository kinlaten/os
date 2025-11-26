#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("wzip: file1 [file2 ...]\n");
    return 1;
  }

  int count = 0;
  char current = EOF; // Initialize to EOF to track first character
  char next;

  // Process all files as a single continuous stream
  for (int i = 1; i < argc; i++) {
    FILE *input = fopen(argv[i], "rb");
    if (input == NULL) {
      printf("wzip: cannot open file %s\n", argv[i]);
      return 1;
    }

    // Read characters from this file
    while ((next = fgetc(input)) != EOF) {
      if (current == EOF) {
        // First character ever across all files
        current = next;
        count = 1;
      } else if (next == current) {
        // Same character, increment count
        count++;
      } else {
        // Different character, write out the previous run
        fwrite(&count, sizeof(int), 1, stdout);
        fwrite(&current, sizeof(char), 1, stdout);
        // Start new run
        current = next;
        count = 1;
      }
    }
    fclose(input);
  }

  // Write the last run if there is one
  if (current != EOF) {
    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&current, sizeof(char), 1, stdout);
  }

  return 0;
}