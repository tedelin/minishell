# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 14:55:19 by tedelin           #+#    #+#              #
#    Updated: 2023/03/21 17:17:55 by tedelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
INCLUDE = -I./include -I./libft
CC = cc
CFLAGS = -g #-Wall -Wextra -Werror -g
SRC =  $(addprefix src/parsing/, ft_parser.c lst_token.c ft_args.c ft_expansion.c ft_env.c ft_dollar.c lst_env.c t_cmd.c lst_cmd.c ft_cd.c ft_pwd.c main.c)
OBJS = $(addprefix obj/, ft_parser.o lst_token.o ft_args.o ft_expansion.o ft_env.o ft_dollar.o lst_env.o t_cmd.o lst_cmd.o ft_cd.o ft_pwd.o main.o)

all: $(NAME)

libft/libft.a:
	make -C libft

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) -Llibft -lft -lreadline

obj/%.o: src/parsing/%.c
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

.PHONY: all clean fclean re
