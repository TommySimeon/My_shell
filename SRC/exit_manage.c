/*
** EPITECH PROJECT, 2018
** minishell
** File description:
** exit
*/

#include "my.h"

int skip_space_exit(char *ligne, int pos)
{
    for (; ligne[pos] == ' ' || ligne[pos] == '\t'; pos++);
    for (; ligne[pos] != ' ' && ligne[pos] != '\0' &&
    ligne[pos] != '\t'; pos++);
    return pos;
}

char *take_exit_value(char *ligne, exit_t *exit_s, char *value_exit)
{
    int j = 0;

    exit_s->pos = skip_space_exit(ligne, exit_s->pos);
    for (; ligne[exit_s->pos] == ' ' || ligne[exit_s->pos] == '(' ||
    ligne[exit_s->pos] == '\t'; exit_s->pos++) {
        if (ligne[exit_s->pos] == '(')
            exit_s->open_par++;
    }
    for (; ligne[exit_s->pos] != ')' && ligne[exit_s->pos] != '\0' &&
    ligne[exit_s->pos] != ' ' && ligne[exit_s->pos] != '\t'; exit_s->pos++) {
        if ((ligne[exit_s->pos] < '0' || ligne[exit_s->pos] > '9')
        && ligne[exit_s->pos] != '-') {
            my_put_error("exit: Expression Syntax.\n");
            return NULL;
        }
        value_exit[j] = ligne[exit_s->pos];
        j++;
    }
    value_exit[j] = '\0';
    return value_exit;
}

void finish_exit(exit_t exit_s, char *value_exit)
{
    int value = string_to_int(value_exit);

    free(value_exit);
    if (exit_s.close_par != exit_s.open_par) {
        if (exit_s.close_par > exit_s.open_par)
            my_put_error("Too many )'s.\n");
        else
            my_put_error("Too many ('s.\n");
        return ;
    }
    if (value < 0) {
        for (; value < 0; value = value + 256);
        exit(value);
    }
    my_putstr("exit\n");
    exit(value % 256);
}

void manage_exit(char *ligne)
{
    exit_t exit_s;
    exit_s.pos = 0;
    exit_s.open_par = 0;
    exit_s.close_par = 0;
    char *value_exit = malloc(sizeof(char) * my_strlen(ligne));

    value_exit = take_exit_value(ligne, &exit_s, value_exit);
    if (value_exit == NULL)
        return ;
    for (; ligne[exit_s.pos] != '\0'; exit_s.pos++) {
        if (ligne[exit_s.pos] != ' ' && ligne[exit_s.pos] != '('
        && ligne[exit_s.pos] != ')') {
            my_put_error("exit: Expression Syntax.\n");
            return ;
        }
        if (ligne[exit_s.pos] == ')')
            exit_s.close_par++;
    }
    finish_exit(exit_s, value_exit);
}