/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 11:22:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/13 18:02:22 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_process(t_data *data)
{
	if (pipe(data->fd) == -1)
	{
		ft_exit(data, "pipe ");
	}
	data->pid = fork();
	if (data->pid == -1)
	{
		ft_exit(data, "pid ");
	}
	if (data->pid == 0)
	{
		ft_child(data);
	}
	else
	{
		if (dup2(data->fd[0], STDIN_FILENO) == -1)
		{
			ft_exit(data, "dup2 ");
		}
		if (close(data->fd[1]) == -1 || close (data->fd[0]) == -1)
		{
			ft_exit(data, "close ");
		}
	}
}

void	ft_child(t_data *data)
{
	if (data->nb_cmd == 2)
	{
		if (data->in == -1)
			ft_exit(data, data->av[1]);
		if (dup2(data->in, STDIN_FILENO) == -1
			|| dup2(data->fd[1], STDOUT_FILENO) == -1)
			ft_exit(data, "dup2 ");
	}
	else if (data->nb_cmd == data->ac - 2)
	{
		if (data->out == -1)
			ft_exit(data, data->av[data->ac - 1]);
		if (dup2(data->out, STDOUT_FILENO) == -1)
			ft_exit(data, "dup2 ");
	}
	if (close(data->fd[0]) == -1 || close(data->fd[1]) == -1)
		ft_exit(data, "dup2 ");
	ft_exec(data);
}

void	ft_exec(t_data *data)
{
	ft_access(data);
	if (!data->cmd_path
		|| execve(data->cmd_path, data->cmd_args, data->env) == -1)
	{
		errno = 127;
		ft_putstr_fd(data->cmd_args[0], 2);
		ft_putendl_fd(": command not found", 2);
		ft_exit(data, "main");
	}
}

void	ft_access(t_data *data)
{
	int	i;

	i = -1;
	data->cmd_args = ft_split(data->av[data->nb_cmd], ' ');
	if (data->cmd_args == NULL)
		return ;
	if (access(data->cmd_args[0], X_OK) == 0)
	{
		data->cmd_path = ft_strdup(data->cmd_args[0]);
		return ;
	}
	data->cmd = ft_strjoin("/", data->cmd_args[0]);
	if (data->cmd == NULL)
		return ;
	while (data->path && data->path[++i])
	{
		data->cmd_path = ft_strjoin(data->path[i], data->cmd);
		if (!data->cmd_path)
			return ;
		if (access(data->cmd_path, X_OK) == 0)
			return ;
		free(data->cmd_path);
		data->cmd_path = NULL;
	}
	return ;
}

char	**ft_path(char **env)
{
	int	i;

	i = 0;
	if (!*env || !env)
	{
		return (NULL);
	}
	while (env[i] && ft_strncmp("PATH=", env[i], 5) != 0)
	{
		i++;
	}
	if (!env[i])
	{
		return (NULL);
	}
	return (ft_split(env[i] + 5, ':'));
}
