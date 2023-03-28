/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:57:57 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/28 17:20:02 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process(t_cmd *cmd, t_pid **lst_pid, int n)
{
	pid_t	pid;
	
	if (pipe(cmd->fd) == -1)
		ft_exit(cmd, lst_pid, "pipe ");
	pid = fork();
	if (pid == -1)
		ft_exit(cmd, lst_pid, "pid ");
	if (pid == 0)
		ft_child(cmd, lst_pid, n);
	else
	{
		pid_lstadd_back(lst_pid, pid_lstnew(pid));
		if (dup2(cmd->fd[0], STDIN_FILENO) == -1)
			ft_exit(cmd, lst_pid, "dup2 ");
		if (close(cmd->fd[1]) == -1 || close (cmd->fd[0]) == -1)
			ft_exit(cmd, lst_pid, "close ");
	}
}

void	ft_child(t_cmd *cmd, t_pid **lst_pid, int n)
{
	if (!cmd->next)
	{
		if (cmd->out == -1)
			ft_exit(cmd, lst_pid, cmd->red);
		if (dup2(cmd->out, STDOUT_FILENO) == -1)
			ft_exit(cmd, lst_pid, "dup2 ");
	}
	else if (n == 1)
	{
		if (cmd->in == -1)
			ft_exit(cmd, lst_pid, cmd->red);
		if (dup2(cmd->in, STDIN_FILENO) == -1
			|| dup2(cmd->fd[1], STDOUT_FILENO) == -1)
			ft_exit(cmd, lst_pid, "dup2 ");
	}
	else if (dup2(cmd->fd[1], STDOUT_FILENO) == -1)
		ft_exit(cmd, lst_pid, "dup2 ");
	if (close(cmd->fd[0]) == -1 || close(cmd->fd[1]) == -1)
		ft_exit(cmd, lst_pid, "dup2 ");
	ft_exec(cmd, lst_pid);
}

void	ft_exec(t_cmd *cmd, t_pid **lst_pid)
{
	char	**args;
	char	*path;
	
	args = ft_lst_to_tab(cmd->args);
	path = ft_access(cmd, args);
	if (path
		|| execve(path, args, env) == -1)
	{
		errno = 127;
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": command not found", 2);
		ft_exit(cmd, lst_pid, "main");
	}
}

char	*ft_access(t_cmd *cmd, char **args, char **env)
{
	char	*path_cmd;
	char	**path;
	char	*tmp_cmd;
	int	i;

	i = -1;
	path = ft_path();
	if (access(args[0], X_OK) == 0)
		return (ft_strdup(args[0]));
	tmp_cmd = ft_strjoin("/", args[0]);
	if (tmp_cmd == NULL)
		return (NULL);
	while (path && path[++i])
	{
		path_cmd = ft_strjoin(path[i], tmp_cmd);
		if (!path_cmd)
			return (NULL);
		if (access(path_cmd, X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
		path_cmd = NULL;
	}
	return (NULL);
}

char	**ft_path(void)
{
	char	**env;
	int	i;

	i = 0;
	env = ft_env(NULL, LST, NULL);
	if (!*env || !env)
		return (NULL);
	while (env[i] && ft_strncmp("PATH=", env[i], 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	return (ft_split(env[i] + 5, ':'));
}

void	ft_exit(t_data *cmd, t_pid **lst_pid, char *msg)
{
	t_pid	*tmp;

	while ((*lst_pid))
	{
		tmp = (*lst_pid);
		(*lst_pid) = (*lst_pid)->next;
		free(tmp);
		tmp = NULL;
	}
	free(*lst_pid);
	free_split(data->cmd_args);
	free_split(data->path);
	free(data->cmd);
	free(data->cmd_path);
	if (data->in != -1)
		close(data->in);
	if (data->out != -1)
		close(data->out);
	if (ft_strncmp(msg, "main", 4) == 0)
		exit(errno);
	perror(msg);
	close(data->fd[0]);
	close(data->fd[1]);
	exit(errno);
}