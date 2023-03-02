# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/27 14:55:19 by tedelin           #+#    #+#              #
#    Updated: 2023/03/02 17:24:03 by tedelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
INCLUDE = -I./include -I./libft
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC =  $(addprefix src/, ft_parser.c ft_token.c lst_token.c ft_args.c)
OBJS = $(addprefix obj/, ft_parser.o ft_token.o lst_token.o ft_args.o)

all: $(NAME)

libft/libft.a:
	make -C libft

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) -Llibft -lft

obj/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $^

clean:
	rm -rf $(OBJS)
	rm -rf obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
