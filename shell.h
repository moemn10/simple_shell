#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* **for read/write buffers** */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* **for command chaining** */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for **convert_number()** */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* **1 if using system getline()** */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct Liststr - singly linked list
 * @num: The number field
 * @str: A string
 * @next: Points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - Contains pseudo-arguements to pass into a function,
 * Allowing uniform prototype for function pointer struct
 * @arg: A string generated from getline containing arguements
 * @argv:An array of strings generated from arg
 * @path: A string path for the current command
 * @argc: The arg count
 * @line_count: The error count
 * @err_num: The error code for exit()s
 * @linecount_flag: If on count this line of input
 * @fname: The program filename
 * @env: linked of list local copy of environ
 * @environ: Customing modified copy of environ from LL env
 * @history: The history node
 * @alias: The alias node
 * @env_changed: On if environ was changed
 * @status: The return status of the last exec'd command
 * @cmd_buf: Add of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: The fd from which to read line input
 * @histcount: The history line number count
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

	char **cmd_buf; /* ** Pointer to cmd ; chain buffer, for memory mangement** */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - Containg a builtin string and related function
 * @type: The builtin command flags
 * @func: The function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* **__shell_loop__.c** */
int mkw(info_t *, char **);
int search_built(info_t *);
void find_lin(info_t *);
void fork_Command(info_t *);

/* **__Parser__.c** */
int linux_command(info_t *, char *);
char *db_ch(char *, int, int);
char *search(info_t *, char *, char *);

/* **loophsh**.c */
int loophsh(char **);

/* **__errors1__.c** */
void _erputs(char *);
int _erputchar(char);
int _putfd_(char x, int fd);
int _putsfd_(char *str, int fd);

/* **__string__.c** */
int _strlength(char *);
int _strgo(char *, char *);
char *start_data(const char *, const char *);
char *_str_dot(char *, char *);

/* **__string1__.c** */
char *_Cp(char *, char *);
char *_str_dupc_root(const char *);
void _puts(char *);
int _putchar(char);

/* **exits.c** */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* **tokenizer.c** */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* **realloc.c** */
char *_mset(char *, char, unsigned int);
void dbfree(char **);
void *_lloc(void *, unsigned int, unsigned int);

/* **__memory.c__** */
int Sysdb(void **);

/* **__atoi__.c** */
int inactive(info_t *);
int is_dlim(char, char *);
int is_alpha(int);
int __atoi(char *);

/* **_errors2__.c** */
int _erratoi_(char *);
void printing_error(info_t *, char *);
int printing_d(int, int);
char *converting_number(long int, int, int);
void rm_com(char *);

/* **__builtin__.c** */
int my_exit(info_t *);
int my_cd(info_t *);
int my_help(info_t *);

/* **__builtin1__.c** */
int my_history(info_t *);
int my_alias(info_t *);
int _unset_alias(info_t *, char *);
int seting_alias(info_t *, char *);
int printing_alias(list_t *);
/* **__get_line__.c** */
ssize_t in_buf(info_t *, char *, size_t);
ssize_t get_in(info_t *);
int _geting_line(info_t *, char **, size_t *);
void sigin_Handler(int);

/* **getinfo.c** */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* **__environment__.c** */
char *get_env(info_t *, const char *);
int my_env(info_t *);
int my_set_env(info_t *);
int my_unset_env(info_t *);
int pop_env_list(info_t *);

/* **getenv.c** */
char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

/* **history.c** */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* **__lists.c__** */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* **__lists1__.c** */
size_t listing_len(const list_t *);
char **list_str(list_t *);
size_t out_list(const list_t *);
list_t *node_start(list_t *, char *, char);
ssize_t Get_node(list_t *, list_t *);

/* **vars.c** */
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
