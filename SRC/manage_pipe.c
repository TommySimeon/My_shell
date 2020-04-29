/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** manage_pipe
*/

#include "my.h"

int manage_simple_redirection(char *buffer, \
    char *place, char *symbol, char *dest)
{
    char *path_file;
    int i = 0;
    char *new_place = malloc(sizeof(char) * (my_strlen(place) + 5));
    int fd = 0;

    if (dest == NULL)
        return 0;
    for (; place[i] != '\0'; i++)
        new_place[i] = place[i];
    new_place[i] = '/';
    new_place[i + 1] = '\0';
    path_file = add_place(dest, new_place);
    ln_arg = ln_arg + 2;
    if (symbol[1] == '\0')
        fd = open(path_file, O_CREAT | O_WRONLY | O_TRUNC, 0777);
    else
        fd = open(path_file, O_CREAT | O_WRONLY | O_APPEND, 0777);
    write(fd, buffer, my_strlen(buffer));
    close(fd);
    return 25;
}

int create_output_file(char *buffer, char *place, char *symbol, char *dest)
{
    char *path_file;
    int fd = 0;

    if (buffer[0] == '\0')
        return 0;
    if (symbol[0] == '|')
        path_file = add_place("/manage_pipe/pipe.tmp", place);
    if (symbol[0] == '>')
        return manage_simple_redirection(buffer, place, symbol, dest);
    fd = open(path_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    write(fd, buffer, my_strlen(buffer));
    close(fd);
    return 1;
}

pid_t init_pipe(int *pipe_fd, pid_t pid)
{
    if (pipe(pipe_fd) == -1)
        exit(1);
    pid = fork();
    if (pid == -1)
        exit(1);
    return pid;
}

int manage_exe_pipe(char **env, char *cmd, char **board_arg, char *place)
{
    int *pipe_fd = malloc(sizeof(int) * 2);
    char *buffer = malloc(sizeof(char) * 5000);
    pid_t pid;
    char **arg_exe = take_arg_exe(board_arg[ln_arg]);

    if (board_arg[ln_arg + 2] != NULL && my_strcmp(board_arg[ln_arg + 2], \
        board_arg[ln_arg]) == 1) {
        return manage_exe(board_arg, env, NULL, place);
    }
    pid = init_pipe(pipe_fd, pid);
    if (pid == 0) {
        close(pipe_fd[0]);
        if (dup2(pipe_fd[1], 1) == -1)
            exit(1);
        else if (execve(cmd, arg_exe, env) == -1) {
            manage_error_exe(cmd);
            return 0;
        }
    } else {
        wait(&pid);
        close(pipe_fd[1]);
        read(pipe_fd[0], buffer, 5000);
    }
    return create_output_file(buffer, place, board_arg[ln_arg + 1], \
        board_arg[ln_arg + 2]);
}