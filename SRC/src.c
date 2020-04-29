/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** src
*/

#include "../include/my.h"

arg_t *add_node_to_begin(arg_t *list, char **board_arg)
{
    node_arg *new = malloc(sizeof(*new));

    new->board_arg = board_arg;
    new->prev = NULL;
    if (list->tail == NULL) {
        new->next = NULL;
        list->head = new;
        list->tail = new;
    }
    else {
        list->head->prev = new;
        new->next = list->head;
        list->head = new;
    }
    list->length++;
    return list;
}

int my_strcmp(char *str, char *src)
{
    for (int i = 0; 1; i++) {
        if (str[i] != src[i])
            return -1;
        if (str[i] == '\0' && src[i] == '\0')
            return 1;
    }
}

void my_putstr(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        write(1, &str[i], 1);
}

int my_strlen(char *str)
{
    int i = 0;

    for (; str[i] != '\0'; i++);
    return i;
}

char **realloc_my_board(char **board)
{
    char **new = malloc(sizeof(char *) * my_strlen_board(board) + 2);
    int ln = 0;
    int cln = 0;

    for (; board[ln] != NULL; ln++) {
        new[ln] = malloc(sizeof(char) * my_strlen(board[ln]) + 1);
        for (; board[ln][cln] != '\0'; cln++)
            new[ln][cln] = board[ln][cln];
        new[ln][cln] = '\0';
        cln = 0;
    }
    new[ln + 1] = NULL;
    return new;
}