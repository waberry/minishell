# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: berry <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/27 18:40:51 by berry             #+#    #+#              #
#    Updated: 2019/07/25 16:10:50 by berry            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell

CC=gcc

CFLAGS=-Wall -Wextra -Werror

SRC=./main.c ./utils.c ./exit.c ./colors.c ./run_command.c ./unsetenv_builtin.c ./setenv_builtin.c ./echo_builtin.c ./cd_builtin.c

OBJ=$(SRC:.c=.o)

RM=rm -f

LIBFT= ./libft/libft.a

$(NAME):$(OBJ)
		make -C ./libft/
		$(CC) $(CFLAGS) -c $(SRC)
		$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $(NAME)

all:@$(NAME)

clean:
	$(RM) $(OBJ)
	make clean -C ./libft/

fclean: clean
		rm -f $(NAME)
		make fclean -C ./libft/

re: fclean all

.PHONY: all clean fclean re
