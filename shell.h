#ifndef __SHELL__H_
#define __SHELL__H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <sys/wait.h>

#define BUFF_SIZE 1024
#define DELIM_DIRS ":"
#define ENV_PATH "PATH"

extern char **environ;

/**
* struct directory_list - Definition for a node in linked list
* @dir_name: The direcorty path
* @next: Pointer to the the next node in the
* directoy_list linked list
*/
typedef struct directory_list
{
	char *dir_name;
	struct directory_list *next;
} dir_l;

size_t _strlen(const char *str);
void prompt(void);
char *_strcat(char *dest, char *src);
void free_memory(char **buffer);
void free_tokens(char **tokens);
char *_strchr(char *s, char c);
char *_strncpy(char *dest, char *src, int n);
char **split_string(char *str, int *num_ags);
char *_getenv(char *name);
dir_l *add_node_begin(dir_l **head, char *str);
dir_l *build_env_dirs(dir_l **head, char *str);
void free_dirl(dir_l **head);
char *searchfile(dir_l *head, char *name);
char *search_prog(char *name);
void upd_cmd(char ***args, char *str, int ntoks, size_t str_len, char *name);
int execute_builtin_command(char **args);
int execute_external_command(char **args, char **env);
int execute_command(char **args, char **env);
char *_memcpy(char *dest, char *src, unsigned int n);
int _strcmp(char *s1, char *s2);
char *_strdup(char *src);
char **tokenize(char *commands);
int _strncmp(const char *s1, char *s2, size_t n);
void free_args(char ***args);
int isProgramPath(char *path);
void update_cmd(char **args, int index, char *progPath);
char *_strcpy(char *dest, const char *src);
size_t _strcspn(const char *str, const char *reject);
void exitShell(void);
int handleCommand(const char *command);
void shell_loop(char **env, char *argv[]);
void process_command(char *command, char **env);
char *read_command(void);
void cleanup(char *command, char **args, char *progPath);

#endif /* __SHELL__H_ */
