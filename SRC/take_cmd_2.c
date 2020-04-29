/*
** EPITECH PROJECT, 2019
** take_cmd_2.c
** File description:
** take_cmd_2.c
*/

#include "my.h"

slash_t part_cmd(slash_t slash)
{
    for (; slash.str[slash.i] == ' ' || slash.str[slash.i] == '\t'; \
        slash.i++);
    for (slash.cln = 0; slash.str[slash.i] != ';' && \
        slash.str[slash.i] != '\0' && slash.str[slash.i] != '|' \
        && slash.str[slash.i] != '>' && slash.str[slash.i] != '&' \
        && check_redirection(slash.str, slash.i, slash.cln) != 1; slash.i++) {
        slash.board[slash.ln][slash.cln] = slash.str[slash.i];
        slash.cln++;
    }
    slash.cln--;
    for (; slash.board[slash.ln][slash.cln] == ' '; slash.cln--);
    slash.board[slash.ln++][slash.cln + 1] = '\0';
    for (; slash.str[slash.i] == ' ' || \
        slash.str[slash.i] == '\t'; slash.i++);
    return slash;
}

arg_t *slash_cmd(char *str)
{
    slash_t slash;

    slash.str = str;
    slash.end_status = 0;
    slash.arg = malloc(sizeof(*slash.arg));
    slash.board = malloc_my_board(my_strlen(str), my_strlen(str));
    slash.ln = 0;
    slash.cln = 0;
    for (slash.i = 0; slash.i < my_strlen(str); slash.ln++, slash.i++) {
    slash = part_cmd(slash);
    if (slash.str[slash.i] == ';' || slash.str[slash.i] == '\0') {
            slash.board[slash.ln] = NULL;
            slash.arg = add_node_to_begin(slash.arg, slash.board);
            slash.ln = -1;
            slash.board = malloc_my_board(my_strlen(slash.str), \
            my_strlen(slash.str));
    } else
            slash = part_redirections(slash);
        if (slash.end_status == 1)
            return slash.arg;
    }
    return slash.arg;
}
