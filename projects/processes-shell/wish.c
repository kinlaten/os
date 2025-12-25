#include "wish.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

FILE *in = NULL;
char *path[BUFF_SIZE] = {NULL};

int main(int argc, char *argv[]) {

  int mode = INTERACTIVE_MODE; // default
  in = stdin;
  path[0] = strdup("/bin");

  if (argc > 1) {
    mode = BATCH_MODE;

    if (argc > 2 || (in = fopen(argv[1], "r")) == NULL) {
      printError();
      exit(EXIT_FAILURE);
    }
  }

  char *line = NULL;
  size_t len = 0;

  while (1) {
    if (mode == INTERACTIVE_MODE) {
      printf("wish> ");
    }

    // Read input
    if (getline(&line, &len, in) == -1)
      break;

    //  Replace \n by \0 to end the line
    line[strcspn(line, "\n")] = '\0';
    char *single_command;
    char **command_list = fetchCommands(line);
    int cmd_i = 0;
    int prc_i = 0;
    pid_t pid_list[BUFF_SIZE];

    while ((single_command = command_list[cmd_i++]) != NULL) {
      // char *args[] = parseInput(single_command);
      pid_t pid = executeCommand(single_command);
      if (pid > 0) {
        pid_list[prc_i++] = pid;
      }
    }

    for (int i = 0; i < prc_i; i++) {
      waitpid(pid_list[i], NULL, 0);
    }
    free(command_list);
  }
  if (in != stdin)
    fclose(in);
  free(line);
  return EXIT_SUCCESS;
}

void printError() { fprintf(stderr, "An error has occurred\n"); }

char **fetchCommands(char *input) {
  char **command_list = malloc(sizeof(char *) * BUFF_SIZE);
  if (command_list == NULL)
    return NULL;

  char *single_command;
  char *input_copy = input;
  size_t cmd_count = 0;

  while ((single_command = strsep(&input_copy, "&")) != NULL) {
    if (strlen(single_command) == 0)
      continue;

    command_list[cmd_count++] = single_command;

    if (cmd_count >= BUFF_SIZE - 1)
      break;
  }
  command_list[cmd_count] = NULL;
  return command_list;
};

CommandResult fetchArgs(char *command) {
  CommandResult res;
  res.args = malloc(sizeof(char *) * BUFF_SIZE);
  res.count = 0;
  char *token;

  while ((token = strsep(&command, " ")) != NULL) {
    if (strlen(token) > 0) {
      res.args[res.count++] = token;
    }
  }
  res.args[res.count] = NULL;
  return res;
};

void free_command(CommandResult *res) {
  if (res->args != NULL) {
    // We only free res->args, NOT the individual strings in res->args[i]
    // because strsep points back to the original input buffer.
    free(res->args);
    res->args = NULL;
  }
  res->count = 0;
}

int executeCommand(char *cmd_string) {
  CommandResult res = fetchArgs(cmd_string);
  char **args = res.args;
  size_t i = res.count;

  if (args[0] == NULL) {
    free_command(&res);
    return -1;
  }

  // BUILT-IN COMMAND
  if (strcmp(args[0], "exit") == 0)
    exit(EXIT_SUCCESS);
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
  }
  //
  // path command
  else if (strcmp(args[0], "path") == 0) {
    // Clear old paths
    for (int k = 0; path[k] != NULL; k++) {
      free(path[k]);
      path[k] = NULL;
    }
    // Set new paths
    int k = 0;
    while (args[k + 1] != NULL && k < BUFF_SIZE - 1) {
      path[k] = strdup(args[k + 1]);
      k++;
    }
    path[k] = NULL;
    // builtin command dont fork
  } else {
    // EXTERNAL COMMAND
    char abs_path[1024];
    size_t pid_count = 0;
    size_t c = 0;
    if (findPath(abs_path, args[0])) {
      pid_t pid = fork();

      if (pid < 0) {
        printError();
      } else if (pid == 0) {
        redirect(args);

        execv(abs_path, args);

        fprintf(stderr, "Failed at child process\n");
      } else {
        free_command(&res);
        return pid;
      }
    } else {
      printError(); // path not found
    };
  }
  free_command(&res);
  return -1;
}
void redirect(char **args) {
  char *filename = NULL;
  for (int i = 1; args[i] != NULL; i++) {
    if (strcmp(args[i], ">") == 0) {
      if (args[i + 1] == NULL || args[i + 2] != NULL) {
        printError();
        exit(EXIT_FAILURE);
      }
      filename = args[i + 1];
      args[i] = NULL; // slice to get sub command
      //
      //
      // Get input from stdout, redirect to file
      int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

      if (fd < 0) {
        fprintf(stderr, "Cannot open file\n");
        exit(EXIT_FAILURE);
      }
      dup2(fd, 1); // 1 is stdout
      close(fd);
      break;
    }
  }
  return;
}

int findPath(char abs_path[], char *command_name) {

  for (int j = 0; path[j] != NULL; j++) {
    // Construct the string: /bin/ls
    snprintf(abs_path, BUFF_SIZE, "%s/%s", path[j], command_name);
    if (access(abs_path, X_OK) == 0) {
      return 1; // true
    }
  }
  return 0;
}
