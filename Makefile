##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## Makefile
##

SRC	=	SRC/main.c \
		SRC/src.c \
		SRC/gnl.c \
		SRC/exit_manage.c \
		SRC/manage_setenv.c \
		SRC/manage_unsetenv.c \
		SRC/set_env.c \
		SRC/manage_setenv_2.c \
		SRC/manage_exe.c \
		SRC/manage_cd.c \
		SRC/my_shell.c \
		SRC/src_2.c \
		SRC/src_3.c \
		SRC/manage_pipe.c \
		SRC/exec_bin.c \
		SRC/manage_exe_2.c \
		SRC/manage_exe_3.c \
		SRC/take_cmd.c \
		SRC/take_cmd_2.c \
		SRC/handling_alias.c

NAME	=	mysh

CC	= gcc -Wall -Wextra -Iinclude

RM	=	rm -f

OBJ	=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
	$(CC) -o  $(NAME) $(OBJ)

clean:
	$(RM) $(OBJ)
	$(RM) *~
	$(RM) *#

fclean:	clean
	$(RM) $(NAME)
	$(RM) *.o

re:	fclean all

.PHONY:	fclean all re clean
