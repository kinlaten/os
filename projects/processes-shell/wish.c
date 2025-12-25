#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  FILE *input_source = stdin;

  if (argc > 2) {
    fprintf(stderr, "Too much arguments");
    exit(EXIT_FAILURE);
  }

  if (argc == 2) {
    input_source = fopen(argv[1], "r");
    if (input_source == NULL) {
      fprintf(stderr, "Can not read command!");
      exit(EXIT_FAILURE);
    }
  }

  char *line = NULL;
  size_t len = 0;
  char *path[20] = {NULL};
  path[0] = strdup("/bin");

  while (1) {
    if (argc == 1) {
      printf("wish> ");
      fflush(stdout); // Ensure prompt prints before enter input
    }

    // Read input
    if (getline(&line, &len, input_source) == -1)
      break;

    // Replace \n by \0 to end the line
    line[strcspn(line, "\n")] = '\0';

    char *commmand_ptr = line; // copy of current line of input, because strsep
                               // modify he original
    char *single_command;
    pid_t pids[64];
    int cmd_count = 0;

    while ((single_command = strsep(&commmand_ptr, "&")) != NULL) {
      if (strlen(single_command) == 0)
        continue;

      // Args
      char *args[64];
      char *token;
      size_t i = 0;

      while ((token = strsep(&single_command, " ")) != NULL) {
        if (strlen(token) > 0) {
          args[i++] = token;
        }
      }

      args[i] = NULL;

      // BUILT-IN COMMAND
      if (args[0] == NULL) {
        continue;
      } else if (strcmp(args[0], "exit") == 0)
        break;
      //
      // cd command
      else if (strcmp(args[0], "cd") == 0) {
        if (i != 2) {
          fprintf(stderr, "Usage: cd <dir>!");
        } else {
          if (chdir(args[1]) != 0) {
            fprintf(stderr, "No such directory!");
          }
        }
        continue;
        //
        // path command
      } else if (strcmp(args[0], "path") == 0) {
        for (int k = 0; path[k] != NULL; k++) {
          free(path[k]);
          path[k] = NULL;
        }
        int k = 0;
        while (args[k + 1] != NULL && k < 19) {
          path[k] = strdup(args[k + 1]);
          k++;
        }
        path[k] = NULL;
        continue;
      }

      // REDIRECTION
      char *filename = NULL;
      int redirection_error = 0;
      for (int x = 1; args[x] != NULL; x++) {
        if (strcmp(args[x], ">") == 0) {
          if (args[x + 1] == NULL || args[x + 2] != NULL) {
            fprintf(stderr,
                    "An error has occurred\n"); // Invalid redirection: no
                                                // filename, no ending null
            redirection_error = 1;
            break;
          }
          filename = args[x + 1];
          args[x] = NULL; // slice to get sub command
          break;
        }
      }

      if (redirection_error)
        continue;

      // EXTERNAL COMMAND
      char command[1024];
      int found = 0;

      for (int j = 0; path[j] != NULL; j++) {
        // Construct the string: /bin/ls
        snprintf(command, sizeof(command), "%s/%s", path[j], args[0]);
        if (access(command, X_OK) == 0) {
          found = 1;
          break;
        }
      }

      if (!found) {
        fprintf(stderr, "Command not found\n");
        continue;
      }

      // SUB PROCESS
      pid_t rc = fork();

      if (rc < 0) {
        fprintf(stderr, "Something is wrong!!");
        exit(EXIT_FAILURE);

      } else if (rc == 0) {
        if (filename != NULL) { // Handle redirection
          int fd =
              open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

          if (fd < 0) {
            fprintf(stderr, "Cannot open file\n");
            exit(EXIT_FAILURE);
          }
          dup2(fd, 1); // 1 is stdout
          close(fd);
        }

        execv(command, args);
        fprintf(stderr, "Failed at child process\n");
        exit(EXIT_FAILURE);

      } else {
        // wait(NULL); //we wait for all sub processes rather than a single
        pids[cmd_count++] = rc;
      }
    }
    for (int n = 0; n < cmd_count; n++) {
      waitpid(pids[n], NULL, 0);
    }
  }
  if (input_source != stdin)
    fclose(input_source);
  free(line);
  return EXIT_SUCCESS;
}
