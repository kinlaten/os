#ifndef WISH_H
#define WISH_H

#include <stdio.h>     // For FILE and size_t
#include <sys/types.h> // For pid_t

#define INTERACTIVE_MODE 1
#define BATCH_MODE 2
#define BUFF_SIZE 256

typedef struct CommandResult {
  char **args;
  size_t count;
} CommandResult;

// Function Prototypes
void printError();
char **fetchCommands(char *input);
int executeCommand(char *cmd_string);
CommandResult fetchArgs(char *command);
void free_command(CommandResult *res);
void redirect(char **args);
int findPath(char abs_path[], char *command_name);

#endif
