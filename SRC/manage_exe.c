/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** manage_exe
*/

#include "my.h"

char **take_arg_exe(char *str)
{
    char **arg = malloc_my_board(my_strlen(str), my_strlen(str));
    int i = 0;
    int ln = 0;
    int cln = 0;

    for (; str[i] != '\0'; ln++) {
        for (; str[i] == ' ' || str[i] == '\t'; i++);
        if (str[i] == '\0')
            break;
        for (cln = 0; str[i] != ' ' && str[i] != '\0'
        && str[i] != '\t'; cln++) {
            arg[ln][cln] = str[i];
            i++;
        }
        arg[ln][cln] = '\0';
    }
    arg[ln] = NULL;
    return arg;
}

void print_segfault_error(pid_t pid)
{
    int error = WTERMSIG(pid);

    if (error == 0)
        return ;
    if (error == 8)
        my_put_error("Floating point exception");
    if (error == 11)
        my_put_error("Segmentation Fault");
    if (error == 6)
        my_put_error("Aborted");
    if (WCOREDUMP(pid))
        my_put_error(" (Core Dumped)\n");
    else
        my_put_error("\n");
}

int exe_cmd(char **board_arg, char **env, char *cmd, int ln_arg)
{
    char **arg_exe = take_arg_exe(board_arg[ln_arg]);
    pid_t pid = fork();
    int status = 0;

    if (pid == -1)
        exit(1);
    else if (pid == 0)
        status = execve(cmd, arg_exe, env);
    else
        wait(&pid);
    print_segfault_error(pid);
    if (status == -1)
        manage_error_exe(cmd);
    output_value = WEXITSTATUS(pid);
    kill(pid, 0);
    return 0;
}

int manage_exe(char **board_arg, char **env, char *cmd, char *place)
{
    if (cmd == NULL) {
        ln_arg += 2;
        cmd = take_command(board_arg[ln_arg]);
    }
    if (board_arg[ln_arg + 1] != NULL &&
    ((board_arg[ln_arg + 1][0] == '|' && board_arg[ln_arg + 1][1] == '\0') \
    || board_arg[ln_arg + 1][0] == '<' \
    || board_arg[ln_arg + 1][0] == '>')) {
        return manage_exe_pipe(env, cmd, board_arg, place);
    }
    return exe_cmd(board_arg, env, cmd, ln_arg);
}

void manage_error_exe(char *cmd)
{
    DIR *dir = opendir(cmd);
    struct stat file;
    int test = stat(cmd, &file);

    if (dir != NULL || test != -1) {
        my_put_error(cmd);
        my_put_error(": Permission denied.\n");
    }
    else {
        my_putstr(cmd);
        my_putstr(": Command not found.\n");
    }
}