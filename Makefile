# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 14:55:19 by tedelin           #+#    #+#              #
#    Updated: 2023/04/10 15:39:42 by tedelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
INCLUDE = -I./include -I./libft
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRC =  $(addprefix src/, $(addprefix parsing/, ft_parser.c lst_token.c ft_args.c \
		ft_expansion.c ft_env.c ft_dollar.c lst_env.c t_cmd.c lst_cmd.c ft_env_utils.c main.c) \
		$(addprefix builtins/, ft_cd.c ft_pwd.c ft_echo.c ft_export.c ft_exit.c ft_unset.c env_cmd.c) \
		$(addprefix exec/, ft_exec.c lst_pid.c pipex.c exec_utils.c builtins.c) \
		$(addprefix signaux/, signaux.c))
OBJS = $(patsubst src/%.c, obj/%.o, $(SRC))

all: $(NAME)

libft/libft.a:
	make -C libft

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) -Llibft -lft -lreadline

obj/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
	make -C libft clean
	rm -rf $(OBJS)
	rm -rf obj

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all

val:        $(NAME)
	valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all --suppressions=readline.supp --track-origins=yes ./${NAME}

.PHONY: all clean fclean re
