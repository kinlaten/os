#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *filename = "lorem.txt";
  int flags = O_RDWR | O_APPEND;

  // Start fork from here
  int rc = fork();

  int fd =
      open(filename, flags); // this is low level IO so we dont use FILE* file

  if (fd == -1) {
    perror("Failed to control file");
    return -1;
  }

  // Read file
  char buffer[11];
  ssize_t readBytes = read(fd, buffer, 10);
  if (readBytes == -1) {
    perror("Failed to read file\n");
  } else {
    printf("Successful read\n");
  }

  if (rc == 0) {
    printf("Success read file from children: %s, PID: %d\n", buffer, getpid());
  } else if (rc > 0) {
    printf("Success read file from parent: %s, PID: %d\n ", buffer, getpid());
  } else {
    printf("Can not fork\n");
  }
  /*
    ❯ ./q2
        Successful read
        Success read file from parent: Lorem Ipsu
        Successful read
        Success read file from children: Lorem Ipsu
   */

  // Write into file
  char *data = "\nEdward wrote something here.";
  write(fd, data, strlen(data)); // this will add duplicated data into the file

  close(fd);
  return 0;
}

/*
 * Use gdb to debug forks:
 * https://sourceware.org/gdb/current/onlinedocs/gdb.html/Forks.html
 */
