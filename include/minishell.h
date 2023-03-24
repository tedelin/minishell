/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:54:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/24 18:24:12 by mcatal-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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
	APPEND,
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

// Parsing split arguments - ft_args.c
int					ft_status(char c, int reset);
int					check_sep(char c, char b);
int					ft_len(char *s, int *j);
char				*ft_args(char *s, int reset);
int					make_token(t_token **lst_token, char *s);

// Dollar expansion - ft_dollar.c
char				*ft_var(char *str);
int					len_d(char *s);
char				*ft_dollar(char *s);
// char				*get_var(t_env *env, char *var);

// Environment - ft_env.c
void				ft_build_env(t_env **lst_env, char **env);
char				*ft_get_env(t_env *env, char *var);
void				edit_env(t_env **env, char *var);
void				append_env(t_env **env, char *name);
void				ft_del(t_env **env, char *name);
char				*ft_env(char **env, int get, char *var);

// Expansion - ft_expansion.c
void				new_token(char *s, t_token **new);
int					ft_expansion(t_token **token);

// Get token type - ft_parser.c
int					ft_next_type(char *next);
int					ft_type(t_token **token);
int					check_quotes(char *s);
int					ft_parser(t_token **token);

// Linked list for cmd - lst_cmd.c
void				lstadd_back_cmd(t_cmd **lst, t_cmd *new);
t_cmd				*lstnew_cmd(void);
void				print_cmd(t_cmd **lst);
void				free_cmd(t_cmd **lst);

// Linked list for env - lst_env.c
void				lstadd_back_env(t_env **lst, t_env *new);
t_env				*lstnew_env(char *value);
void				print_env(t_env **lst);
void				free_env(t_env **lst);

// Linked list for tokens - lst_token.c
t_token				*t_lstnew(char *value, int type);
void				t_lstadd_back(t_token **lst, t_token *new);
void				free_lst(t_token **lst);
void				print_lst(t_token **lst);
int					t_lstsize(t_token **lst);

//Token to cmd
int					build_cmd(t_token **lst);

// Buitin cd - ft_cd.c
void				oldpwd(void);
void				pwd(void);
int					cd_size(t_cmd *cmd);
void				ft_cd(t_cmd *cmd);

// Builtin echo - ft_echo.c
int					new_line(t_token **arg, int n);
void				ft_echo(t_cmd *cmd);

// Buitin exit - ft_exit.c
int					ft_exit(t_cmd *cmd);

// Buitin export - ft_export.c
int					check_add(char *s);
void				ft_export(t_cmd *cmd);

// Buitin pwd - ft_pwd.c
char				*ft_pwd(int opt);

// Buitin unset - ft_unset.c
void				ft_unset(t_cmd *cmd);
// Exec - ft_exec.c
int					is_builtin(t_cmd *cmd);
void				free_tab(char **tab);
char				**ft_lst_to_tab(t_token *lst);
int					ft_exec(t_cmd **lst);

#endif