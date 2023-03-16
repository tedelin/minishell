/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:54:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/16 13:22:38 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

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
int					make_token(t_token **lst_token, char *s);

// Get token type
void				get_type(t_token *token);
int					ft_type(t_token **token);

// Check for syntax error
int					ft_parser(t_token **token);
int					check_quotes(char *s);

// Linked list for tokens
t_token				*t_lstnew(char *value, int type);
void				t_lstadd_back(t_token **lst, t_token *new);
void				free_lst(t_token *lst);
void				print_lst(t_token **lst);

// Expansion
char				*get_var(char **env, char *var);
char				*ft_var(char *new_str);
int					len_d(char **env, char *s);
char				*ft_dollar(char **env, char *s);
t_token				*new_token(t_token *current);
int					ft_expansion(t_token **token);

// Environment
char				**ft_get_env(char **env, int get);

#endif