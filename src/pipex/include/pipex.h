/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 18:11:52 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/11 19:58:17 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
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

void	ft_process(t_data *data);
void	ft_child(t_data *data);
void	ft_exec(t_data *data);
void	ft_access(t_data *data);
char	**ft_path(char **env);

// Utils
void	init_data(t_data *data, int ac, char **av, char **env);
void	free_split(char	**tab);
void	ft_exit(t_data *data, char *msg);

#endif
