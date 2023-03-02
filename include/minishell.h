/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:54:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/02 11:40:04 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>

enum				e_state
{
	DOUBLE = 2,
	SIMPLE = 1,
	SPLIT = 0
};

enum				e_type
{
	WORD = 0,
	FD = 1,
	LIM = 2,
	IN = 3,
	OUT = 4,
	HIN = 5,
	HOUT = 6,
	PIPE = 7
};

typedef struct s_token
{
	char			*value;
	enum e_type		type;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd
{
	t_token			*arg;
	t_token			*red;
	int				fd_in;
	int				fd_out;
	struct s_cmd	*next;
}					t_cmd;

// Parsing split arguments
int					ft_status(char c);
int					ft_len(char *s, int *j);
char				*ft_args(char *s);
t_token				*make_token(char *s);
void				get_type(t_token *token);
void				ft_type(t_token **token);

// Linked list for tokens
t_token				*t_lstnew(char *value, int type);
void				t_lstadd_back(t_token **lst, t_token *new);

#endif