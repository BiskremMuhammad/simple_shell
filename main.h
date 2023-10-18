#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include <signal.h>

/* define constants */
#define EXT_CMD 1
#define INT_CMD 2
#define PATH_CMD 3
#define INVALID_CMD -1

#define min(x, y) (((x) < (y)) ? (x) : (y))

/**
 *struct map - mapper obj 
 *
 *@cmd: command name
 *@func: function to run
 */

typedef struct map
{
	char *cmd;
	void (*func)(char **cmd);
} func_map;

extern char **envs;
extern char *lines;
extern char **cmds;
extern char *shell_name;
extern int status;

void non_interactive(void);
void initializer(char **cur_cmd, int cmd_type);

/* def builtin funcs */
void env(char **);
void quit(char **);

/* descrip functions */
char *_getenv(char *);
void print(char *, int);
int _strlen(char *);
int _atoi(char *);
void _strcpy(char *, char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);
int _strspn(char *, char *);
int _strcspn(char *, char *);
char **tokenizer(char *, char *);
char *_strchr(char *, char);
char *_strtok_r(char *, char *, char **);
void *_realloc(void *ptr, unsigned int old, unsigned int new_size);
void ctrl_c_handler(int);
void remove_newline(char *);
void remove_comment(char *);
char *check_path(char *);
void (*get_func(char *))(char **);
int parse_cmd(char *);
void exec_cmd(char **, int);

#endif  /* MAIN_H */
