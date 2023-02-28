# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tedelin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 10:52:51 by tedelin           #+#    #+#              #
#    Updated: 2023/02/13 18:47:11 by tedelin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I./include -I./libft
SRC = $(addprefix src/, pipex.c utils.c main.c)
OBJ = $(addprefix obj/, pipex.o utils.o main.o)
SRC_BONUS = $(addprefix src/, bonus_pipex.c bonus_utils.c bonus_lst.c bonus_main.c)
OBJ_BONUS = $(addprefix obj/, bonus_pipex.o bonus_utils.o bonus_lst.o bonus_main.o)
LIBFT = -Llibft -lft

all: $(NAME) $(NAME_BONUS)

libft/libft.a:
	make -C libft

$(NAME): $(OBJ) libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) $(LIBFT) -o $@

$(NAME_BONUS): $(OBJ_BONUS) libft/libft.a
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ_BONUS) $(LIBFT) -o $@

obj/%.o: src/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	make -C libft clean
	rm -f $(OBJ) $(OBJS_BONUS)
	rm -rf obj

fclean:	clean
	make -C libft fclean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re