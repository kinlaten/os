#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define handle_error(msg)                                                      \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (1)

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Usage: %s <pages> <trials>", argv[0]);
    exit(EXIT_FAILURE);
  }

  long pagesize = sysconf(_SC_PAGESIZE); // 4KB
  long jump = pagesize / sizeof(int);    // 4KB/4B = 1KB
  int pages = atoi(argv[1]);
  int trials = atoi(argv[2]);

  if (pages <= 0 || trials <= 0) {
    fprintf(stderr, "Invalid input\n");
    exit(EXIT_FAILURE);
  }

  int *a = calloc(
      pages, pagesize); /* abbr: clean allocation. Set all pages to bit zero */

  struct timespec start, end;

  // start timer
  if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start) == -1) {
    handle_error("clock_gettime");
  }

  // Access pages
  for (int j = 0; j < trials; j++) {
    for (int i = 0; i < pages * jump; i += jump) {
      a[i] += 1; // just simply add 1 to the initial bit 0 for each page. Not
                 // special
    }
  }

  // end timer
  if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end) == -1) {
    handle_error("clock_gettime");
  }

  // page access time in nanoseconds
  printf("%f\n",
         ((end.tv_sec - start.tv_sec) * 1E9 + end.tv_nsec - start.tv_nsec) /
             (trials * pages));
  free(a);
  return EXIT_SUCCESS;
}
