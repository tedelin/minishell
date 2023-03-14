/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:54:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/14 15:51:10 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>

enum				e_state
{
	SPLIT,
	SIMPLE,
	DOUBLE
};

enum				e_type
{
	WORD,
	FD,
	LIM,
	IN,
	OUT,
	HIN,
	HOUT,
	PIPE
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
int					ft_status(char c, int reset);
int					ft_len(char *s, int *j);
char				*ft_args(char *s);
t_token				*make_token(char *s);

// Get token type
void				get_type(t_token *token);
void				ft_type(t_token **token);

// Check for syntax error
int					ft_parser(t_token **token);
int					check_quotes(char *s);

// Linked list for tokens
t_token				*t_lstnew(char *value, int type);
void				t_lstadd_back(t_token **lst, t_token *new);

// Expansion
void				magic_space(char **s);
void				new_token(t_token *current, t_token *previous);
void				ft_expansion(t_token **token);
int					ft_change(char *value);
char				*ft_dollar(char *new_str);
char				*ft_var(char *new_str);
char				*get_var(char **env, char *var);

#endif