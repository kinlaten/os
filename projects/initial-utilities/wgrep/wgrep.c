#include <stdio.h>
#include <string.h>
int search_str_file(char *str, char *filename) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    printf("wgrep: cannot open file\n");
    return 1;
  }

  char *line = NULL;
  ssize_t nread = 0; // number of char read
  size_t size = 0;

  // find str in line
  while ((nread = getline(&line, &size, file)) != -1) {
    char *pos = strstr(line, str);
    if (pos) {
      printf("%s", line);
    }
  }

  return 0;
}

int search_str_stdin(char *str, FILE *stream) {
  char *line = NULL;
  ssize_t nread = 0; // number of char read
  size_t size = 0;

  // find str in the stream
  while ((nread = getline(&line, &size, stream)) != -1) {
    char *pos = strstr(line, str);
    if (pos) {
      printf("%s", line);
    }
  }

  return 0;
}

int main(int argc, char *argv[]) {
  // arguments: a search term and zero or more files
  if (argc == 1) {
    // given no search term and no file
    printf("wgrep: searchterm [file ...]\n");
    return 1;
  } else if (argc == 2) {
    // given search term but no file
    return search_str_stdin(argv[1], stdin);
  } else {
    // given full arguments
    for (int i = 2; i < argc; i++) {
      if (search_str_file(argv[1], argv[i]) != 0) {
        return 1;
      }
    }
  }

  return 0;
}
