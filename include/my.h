/*
** EPITECH PROJECT, 2018
** my.h
** File description:
** my.h
*/

#ifndef MY_H_
# define MY_H_

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

int ln_arg;
int output_value;

typedef struct node_arg
{
    char **board_arg;
    struct node_arg *next;
    struct node_arg *prev;
} node_arg;

typedef struct arg_t
{
    int pipe_output;
    char *home;
    int length;
    char *place;
    struct node_arg *head;
    struct node_arg *tail;
} arg_t;

typedef struct slash_t
{
    char *str;
    arg_t *arg;
    int end_status;
    int cln;
    int ln;
    char **board;
    int i;
} slash_t;

typedef struct exit_t
{
    int close_par;
    int open_par;
    int pos;
} exit_t;

typedef struct alias
{
    char *alias;
    char *cmd;
} alias_s;

int check_redirection(char *str, int i, int cln);
int search_cmd(arg_t *arg, char **env, char *place, int ln_arg);
char *my_strcpy(char *dest, char *src);
alias_s *handling_alias(char *path);
char *my_strcat(char *dest, char *src);
char *add_pipe_arg(char *str, char *place);
int verif_arg(char *str);
char **more_flag(char **env, char *cmd, arg_t *arg, char *place);
void prepare_pipe(arg_t *arg, char *place);
char **take_arg_exe(char *str);
char **exe_command(arg_t *arg, char **env, char *place);
void manage_pwd(void);
arg_t *slash_cmd(char *str);
char *take_command(char *ligne);
int manage_exe_pipe(char **env, char *cmd, char **board_arg, char *place);
char **more_flag(char **env, char *cmd, arg_t *arg, char *place);
int my_strlen_board(char **board);
int manage_exe(char **board_arg, char **env, char *cmd, char *place);
char *take_place(char **env);
char *add_place(char *path, char *place);
int take_error_count(char *place);
void my_put_nbr(int nb);
char *int_to_char(int nbr);
char *my_revstr(char *str);
int string_to_int(const char *str);
char **add_name_env(char **env, char *arg1);
arg_t *add_node_to_begin(arg_t *list, char **board_arg);
void manage_error_exe(char *cmd);
slash_t part_redirections(slash_t slash);
char *take_home(char **env);
int my_sh(char **env, char *place);
void my_put_error(char *str);
char *add_path(char *dir, char *str, int i, int status);
int manage_cd(char **board, char *home);
char **malloc_my_board(int ln, int cln);
char **manage_unsetenv(char **env, char *str);
void manage_env(char **env, char *str);
char **manage_setenv(char **env, char *str);
char *get_next_line(int fd, int type);
void print_my_board(char **board);
void my_putstr(char *str);
int check_env(char *env, char *flag);
int verif_name_env(char *name);
int my_strcmp(char *str, char *src);
char **realloc_my_board(char **board);
void manage_exit(char *ligne);
int my_strlen(char *str);
int check_and(char **board);
char *my_realloc(char *src, int len);

#endif
