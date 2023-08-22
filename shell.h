#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

#define BUF_SIZE 1024
#define BUF_FLUSH -1

#define NULL_STRING "(nil)"
#define INTERACTIVE_PREFIX "$ "

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096


#define CMD_DEFAULT	0
#define CMD_AND		1
#define CMD_OR		2
#define CMD_CHAIN	3

#define USE_STRTOK 0

extern char **environ;

/* Type Def */
/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains arguements to pass into a function
 *
 * @arg: the string generated from getline() containing args
 * @argv: array of strings generated from arg
 * @path: a string path for the current command
 * @argc: num of arguments
 *
 * @line_count: the error count
 * @err_num: the error code for exit()
 * @linecount_flag: if on count this line of input
 *
 * @fname: the filename
 * @env: linked list local copy of env vars
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 *
 * @status: the return status of the last exec'd command
 *
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;

	unsigned int line_count;
	int err_num;
	int linecount_flag;

	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;

	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

/**
 * struct builtin - contains a builtin string and related function
 * @type: the builtin command flag
 * @func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/* Info Functions */
void set_info(info_t *info, char **av);
void clear_info(info_t *info);
void free_info(info_t *, int);

int replace_string(char **old, char *new);
int replace_alias(info_t *info);
int replace_vars(info_t *info);

/* Env Functions*/
char *_getenv(info_t *info, const char *name);
int _mysetenv(info_t *info);
int _setenv(info_t *info, char *var, char *value);
int _myremoveenv(info_t *info);
int _removeenv(info_t *info, char *var);

char **get_environ(info_t *info);
int _printenv(info_t *info);
int create_env_list(info_t *info);

/* String functions */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
char *_strdup(const char *s);

char *starts_with(const char *s1, const char *s2);
void _puts(char *str);
int _putchar(char c);
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);

char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);
int isDelim(char c, char *delim);
int _putfd(char c, int fd);

/* Memory functions */
char *_memset(char *s, char b, unsigned int n);
void *_realloc(void *, unsigned int, unsigned int);
void ffree(char **pstr);
int bfree(void **addr);

/* Error Functions */
void _eputs(char *str);
int _eputchar(char c);
int _erratoi(char *);
void print_error(info_t *, char *);

/* Linked List */
list_t *add_node(list_t **head, const char *str, int num);
list_t *add_node_end(list_t **head, const char *str, int num);
size_t print_list_str(const list_t *h);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);

size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

/* History Functions */
int build_history_list(info_t *info, char *buf, int linecount);
char *get_history_file(info_t *info);
int read_history(info_t *info);
int write_history(info_t *info);
int renumber_history(info_t *info);

/* Helper functions */
int isInteractive(info_t *info);
int _isalpha(int c);
int _atoi(char *s);
int _putsfd(char *str, int fd);
int print_d(int input, int fd);

char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);

/* Alias helpers */
int unset_alias(info_t *info, char *name);
int set_alias(info_t *info, char *name);
int print_alias(list_t *node);

/* Builtin functions */
int _cd(info_t *info);
int _myexit(info_t *info);
int _history(info_t *info);
int _alias(info_t *info);

/* Path Parsing Functions */
int isExe(info_t *info, char *);
char *split_path(char *pathStr, int start, int stop);
char *parse_path(info_t *info, char *pathStr, char *cmd);

/* Chaining Functions */
int isChain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);

/* Read line */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/* Main shell */
int myshell(info_t *info, char **av);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

#endif
