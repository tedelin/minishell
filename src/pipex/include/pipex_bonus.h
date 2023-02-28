/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:11:52 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/11 14:53:47 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/types.h>

typedef struct s_data
{
	int		fd[2];
	int		in;
	int		out;
	int		nb_cmd;
	int		ac;
	int		status;
	int		here_doc;
	pid_t	pid;
	char	*cmd_path;
	char	*cmd;
	char	**cmd_args;
	char	**env;
	char	**path;
	char	**av;
}		t_data;

typedef struct s_pid
{
	pid_t			content;
	struct s_pid	*next;
}	t_pid;

// Pipex bonus
void	ft_process(t_data *data, t_pid **lst_pid);
void	ft_child(t_data *data, t_pid **lst_pid);
void	ft_access(t_data *data);
char	**ft_path(char **env);
void	ft_exec(t_data *data, t_pid **lst_pid);

// Utils
void	init_data(t_data *data, int ac, char **av, char **env);
void	free_split(char **tab);
void	ft_heredoc(t_data *data, int ac, char **av);
void	ft_exit(t_data *data, t_pid **lst_pid, char *msg);

// Lstcustom
t_pid	*pid_lstnew(pid_t content);
t_pid	*pid_lstlast(t_pid *lst);
void	pid_lstadd_back(t_pid **lst, t_pid *new);

#endif
