/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:54:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/04 21:17:54 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

extern int			g_exit;

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
	LST,
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
	int				in;
	int				out;
	int				fd[2];
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pid
{
	pid_t			content;
	struct s_pid	*next;
}					t_pid;

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

// Environment - ft_env_utils.c
void				ft_build_env(t_env **lst_env, char **env);
void				ft_get_env(t_env *env, char *var, char **res);
void				edit_env(t_env **env, char *var);
void				append_env(t_env **env, char *name);
void				ft_del(t_env **env, char *name);

// Environment - ft_env.c
t_env				*ft_env(char **env, int get, char *var, char **res);

// Expansion - ft_expansion.c
void				magic_space(char *s, int rm);
void				ft_expand(t_token **new, char *s, int type);
void				new_token(t_token **new, char *s, int type);
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
int					env_lstsize(t_env **lst);

// Linked list for tokens - lst_token.c
t_token				*t_lstnew(char *value, int type);
void				t_lstadd_back(t_token **lst, t_token *new);
void				free_lst(t_token **lst);
void				print_lst(t_token **lst);
int					t_lstsize(t_token **lst);

//Token to cmd
t_token				*ft_arg_and_red(t_token *cur, t_cmd *lst_cmd);
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
void				ft_exit_free(t_cmd **lst, char *s, int state);
int					ft_exit(t_cmd *cmd, t_cmd **lst_cmd);

// Buitin export - ft_export.c
int					check_add(char *s);
void				ft_export(t_cmd *cmd);

// Buitin pwd - ft_pwd.c
void				ft_pwd_cmd(t_cmd *cmd);
char				*ft_pwd(int opt);

// Buitin unset - ft_unset.c
void				ft_unset(t_cmd *cmd);

// Buitin env - env_cmd.c
void				env_cmd(t_cmd *cmd);

// Exec - ft_exec.c
int					is_builtin_child(t_cmd *cmd, t_cmd **lst_cmd);
int					is_builtin_no_child(t_cmd *cmd, t_cmd **lst_cmd);

// Exec - ft_exec.c
void				ft_heredoc(t_cmd *cmd);
void				close_before(t_cmd *cmd, int type);
void				red_loop(t_token *red, t_cmd *cur);
void				make_red(t_cmd **lst);
int					launch_exec(t_cmd **lst);

// Exec Utils - exec_utils.c
void				tab_free(char **tab);
char				**ft_lst_to_tab(t_token *lst);
char				**ft_lst_to_tab_env(t_env *lst);
void				ft_wait(t_pid *lst);
void				exit_child(t_cmd **lst_cmd, t_pid **lst, char *msg);

// Lstcustom
t_pid				*pid_lstnew(pid_t content);
t_pid				*pid_lstlast(t_pid *lst);
void				pid_lstadd_back(t_pid **lst, t_pid *new);

// Pipex - pipex.c
void				ft_process(t_cmd *cmd, t_pid **lst_pid, t_cmd **lst_cmd);
void				ft_child(t_cmd *cmd, t_pid **lst_pid, t_cmd **lst_cmd);
void				ft_exec(t_cmd *cmd, t_pid **lst_pid, t_cmd **lst_cmd);
char				*ft_access(char **args, char **env);
char				**ft_path(char **env);

// Signaux - signaux.c
void				sigint_handler(int sig);
void				set_sign(void);

#endif