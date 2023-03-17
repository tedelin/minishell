/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:54:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/17 16:58:56 by tedelin          ###   ########.fr       */
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

enum				e_env
{
	INIT,
	GET,
	ADD,
	EDIT,
	FREE,
};

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}					t_env;

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
void				free_lst(t_token **lst);
void				print_lst(t_token **lst);

// Linked list for env
void				lstadd_back_env(t_env **lst, t_env *new);
t_env				*lstnew_env(char *value);
void	print_env(t_env **lst);
void	free_env(t_env **lst);

// Dollar expansion
char				*get_var(t_env *env, char *var);
char				*ft_var(char *str);
int					len_d(t_env *env, char *s);
char				*ft_dollar(t_env *env, char *s);

// Expansion
t_token				*new_token(t_token *current);
int					ft_expansion(t_token **token);

// Environment
t_env				*ft_get_env(char **env, int get, char *var);
void				ft_build_env(t_env **lst_env, char **env);

//Builtins
void	ft_export(char *name);

#endif