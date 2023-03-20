/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:54:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/20 15:59:43 by tedelin          ###   ########.fr       */
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
	RIN,
	ROUT,
	DRIN,
	DROUT,
	PIPE
};

enum				e_env
{
	INIT,
	GET,
	ADD,
	EDIT,
	DEL,
	FREE,
	PRINT,
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
void				print_env(t_env **lst);
void				free_env(t_env **lst);

// Linked list for cmd
void				lstadd_back_cmd(t_cmd **lst, t_cmd *new);
t_cmd				*lstnew_cmd(void);
void				print_cmd(t_cmd **lst);
void				free_cmd(t_cmd **lst);

// Dollar expansion
char				*get_var(t_env *env, char *var);
char				*ft_var(char *str);
int					len_d(char *s);
char				*ft_dollar(char *s);

// Expansion
t_token				*new_token(t_token *current);
int					ft_expansion(t_token **token);

// Environment
void				ft_build_env(t_env **lst_env, char **env);
char				*ft_get_env(t_env *env, char *var);
void				edit_env(t_env **env, char *var);
void				ft_del(t_env **env, char *name);
char				*ft_env(char **env, int get, char *var);

//Token to cmd
int					build_cmd(t_token **lst);

//Builtins
void				ft_export(char *name);
void				ft_echo(t_cmd *cmd);
void				ft_pwd(void);

#endif