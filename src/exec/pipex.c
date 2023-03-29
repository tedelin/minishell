/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:57:57 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/29 15:07:30 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process(t_cmd *cmd, t_pid **lst_pid, int n)
{
	pid_t	pid;
	
	if (pipe(cmd->fd) == -1)
		exit_child(cmd, lst_pid, "pipe ");
	pid = fork();
	if (pid == -1)
		exit_child(cmd, lst_pid, "pid ");
	if (pid == 0)
		ft_child(cmd, lst_pid, n);
	else
	{
		pid_lstadd_back(lst_pid, pid_lstnew(pid));
		dup2(cmd->fd[0], STDIN_FILENO);
		close(cmd->fd[1]);
		close (cmd->fd[0]);
	}
}

void	ft_child(t_cmd *cmd, t_pid **lst_pid, int n)
{
	if (!cmd->next)
	{
		if (cmd->out == -1)
			exit_child(cmd, lst_pid, NULL);
		if (dup2(cmd->out, STDOUT_FILENO) == -1)
			exit_child(cmd, lst_pid, "dup2 ");
	}
	else if (n == 1)
	{
		if (cmd->in == -1)
			exit_child(cmd, lst_pid, NULL);
		if (dup2(cmd->in, STDIN_FILENO) == -1
			|| dup2(cmd->fd[1], STDOUT_FILENO) == -1)
			exit_child(cmd, lst_pid, "dup2 ");
	}
	else if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
		exit_child(cmd, lst_pid, "dup2 ");
	if (close(cmd->fd[0]) == -1 || close(cmd->fd[1]) == -1)
		exit_child(cmd, lst_pid, "dup2 ");
	ft_exec(cmd, lst_pid);
}

void	ft_exec(t_cmd *cmd, t_pid **lst_pid)
{
	char	**args;
	char	**env;
	char	*path;
	
	args = ft_lst_to_tab(cmd->arg);
	env = ft_lst_to_tab_env(ft_env(NULL, LST, NULL, NULL));
	path = ft_access(args, env);
	if (!path || execve(path, args, env) == -1)
	{
		errno = 127;
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit_child(cmd, lst_pid, "main");
	}
}

char	*ft_access(char **args, char **env)
{
	char	*path_cmd;
	char	**path;
	char	*tmp_cmd;
	int	i;

	i = -1;
	path = ft_path(env);
	if (access(args[0], X_OK) == 0)
		return (ft_strdup(args[0]));
	tmp_cmd = ft_strjoin("/", args[0], 0);
	if (tmp_cmd == NULL)
		return (NULL);
	while (path && path[++i])
	{
		path_cmd = ft_strjoin(path[i], tmp_cmd, 0);
		if (!path_cmd)
			return (NULL);
		if (access(path_cmd, X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
		path_cmd = NULL;
	}
	return (NULL);
}

char	**ft_path(char **env)
{
	int	i;

	i = 0;
	if (!*env || !env)
		return (NULL);
	while (env[i] && ft_strncmp("PATH=", env[i], 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	return (ft_split(env[i] + 5, ':'));
}

void	exit_child(t_cmd *cmd, t_pid **lst_pid, char *msg)
{
	// t_pid	*tmp;

	// while ((*lst_pid))
	// {
	// 	tmp = (*lst_pid);
	// 	(*lst_pid) = (*lst_pid)->next;
	// 	free(tmp);
	// 	tmp = NULL;
	// }
	// free(*lst_pid);
	// free_split(data->cmd_args);
	// free_split(data->path);
	// free(data->cmd);
	// free(data->cmd_path);
	// if (data->in != -1)
	// 	close(data->in);
	// if (data->out != -1)
	// 	close(data->out);
	// if (ft_strncmp(msg, "main", 4) == 0)
	// 	exit(errno);
	// perror(msg);
	(void) lst_pid;
	(void) msg;
	close(cmd->fd[0]);
	close(cmd->fd[1]);
	exit(errno);
}