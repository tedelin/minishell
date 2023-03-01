/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:54:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/01 17:43:15 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
enum state {DOUBLE = 2, SIMPLE = 1, SPLIT = 0};

enum type {WORD = 0, FD = 1, LIM = 2, RIN = 3, ROUT = 4, DRIN = 5, DROUT = 6, PIPE = 7};

typedef struct s_token
{
	char			*value;
	int				type; // change to enum
	struct s_token *next;
}	t_token;

typedef struct s_cmd
{
	t_token *arg;
	t_token *red;
	int	fd_in;
	int	fd_out;
	struct s_cmd *next;
}	t_cmd;

// Parsing split arguments
int		ft_status(char c);
int		ft_len(char *s, int *j);
char	*ft_args(char *s);
t_token	*make_token(char *s);

// Linked list for tokens
t_token	*t_lstnew(char *value, int type);
void	t_lstadd_back(t_token **lst, t_token *new);

#endif
