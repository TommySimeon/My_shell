/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** take cmd
*/

#include "my.h"

void prepare_pipe(arg_t *arg, char *place)
{
    if (arg->pipe_output == 1) {
        arg->pipe_output = 0;
        ln_arg = ln_arg + 1;
        if (verif_arg(arg->tail->board_arg[ln_arg]) == 0)
            arg->tail->board_arg[ln_arg] = \
        add_pipe_arg(arg->tail->board_arg[ln_arg], place);
    }
}

char *take_command(char *ligne)
{
    char *cmd = malloc(sizeof(char) * my_strlen(ligne));
    int j = 0;
    int i = 0;

    for (; ligne[i] == ' ' || ligne[i] == '\t'; i++);
    for (; ligne[i] != ' ' && ligne[i] != '\0' &&
    ligne[i] != '\t' && ligne[i] != '|'; i++) {
        cmd[j] = ligne[i];
        j++;
    }
    cmd[j] = '\0';
    return cmd;
}

int check_redirection(char *str, int i, int cln)
{
    if (str[i] == '<' && cln != 0)
        return 1;
    return 0;
}

slash_t part_redirections(slash_t slash)
{
    if (slash.board[slash.ln - 1][0] == '&' || \
        slash.board[slash.ln - 1][0] == '|' || \
        check_redirection(slash.board[slash.ln - 1], 0, 1) == 1 ||
    slash.board[slash.ln - 1][0] == '>' || \
    slash.board[slash.ln - 1][0] == '\0') {
        slash.board[slash.ln - 2] = NULL;
        slash.arg = add_node_to_begin(slash.arg, slash.board);
        return slash;
    }
    slash.cln = 0;
    slash.board[slash.ln][slash.cln++] = slash.str[slash.i];
    if (slash.str[slash.i + 1] == '&' || slash.str[slash.i + 1] == '>' || \
    slash.str[slash.i + 1] == '<' || slash.str[slash.i + 1] == '|') {
        slash.i++;
        slash.board[slash.ln][slash.cln++] = slash.str[slash.i];
    }
    if (slash.board[slash.ln][0] == '\0')
        return slash;
    slash.board[slash.ln][slash.cln] = '\0';
    return slash;
}