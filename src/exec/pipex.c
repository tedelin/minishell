/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:28:26 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/11 07:25:36 by mcatal-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process(t_cmd *cmd, t_pid **lst_pid, t_cmd **lst_cmd)
{
	pid_t	pid;

	if (!cmd || (cmd->next && pipe(cmd->fd) == -1))
		return ;
	if (cmd->next && cmd->next->in == -2)
		cmd->next->in = cmd->fd[0];
	else if (cmd->next && cmd->next->in != -2)
		close(cmd->fd[0]);
	pid = fork();
	if (pid == -1)
		exit_child(lst_cmd, lst_pid, "pid ");
	if (pid == 0)
	{
		ft_signal(CHILD);
		ft_child(cmd, lst_pid, lst_cmd);
	}
	else
	{
		ft_signal(IGNORE);
		pid_lstadd_back(lst_pid, pid_lstnew(pid));
		if (cmd->fd[1] > 2)
			close(cmd->fd[1]);
		if (cmd->in > 2)
			close(cmd->in);
	}
}

void	ft_child(t_cmd *cmd, t_pid **lst_pid, t_cmd **lst_cmd)
{
	if (cmd->in == -1 || cmd->out == -1)
		exit_child(lst_cmd, lst_pid, "main");
	if (cmd->in > 2)
	{
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->out > 2)
	{
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
	else if (cmd->next)
		dup2(cmd->fd[1], STDOUT_FILENO);
	if (cmd->next)
	{
		close(cmd->fd[0]);
		close(cmd->fd[1]);
	}
	if (is_builtin_child(cmd, lst_cmd))
		ft_exec(cmd, lst_pid, lst_cmd);
	exit_child(lst_cmd, lst_pid, "main");
}

void	ft_exec(t_cmd *cmd, t_pid **lst_pid, t_cmd **lst_cmd)
{
	char	**args;
	char	**env;
	char	*path;

	args = ft_lst_to_tab(cmd->arg);
	if (!args || !args[0])
	{
		tab_free(args);
		exit_child(lst_cmd, lst_pid, "main");
		return ;
	}
	env = ft_lst_to_tab_env(ft_env(NULL, LST, NULL, NULL));
	path = ft_access(args, env);
	if (!path || execve(path, args, env) == -1)
	{
		ft_putstr_fd(args[0], 2);
		ft_putendl_fd(": command not found", 2);
		free(path);
		tab_free(args);
		tab_free(env);
		errno = 127;
		exit_child(lst_cmd, lst_pid, "main");
	}
}

char	*ft_access(char **args, char **env)
{
	char	*path_cmd;
	char	**path;
	char	*tmp_cmd;
	int		i;

	i = -1;
	path = ft_path(env);
	if (args && access(args[0], X_OK) == 0)
		return (tab_free(path), ft_strdup(args[0]));
	tmp_cmd = ft_strjoin("/", args[0], 0);
	if (tmp_cmd == NULL)
		return (tab_free(path), NULL);
	while (path && path[++i])
	{
		path_cmd = ft_strjoin(path[i], tmp_cmd, 0);
		if (!path_cmd)
			return (free(tmp_cmd), tab_free(path), NULL);
		if (access(path_cmd, X_OK) == 0)
			return (free(tmp_cmd), tab_free(path), path_cmd);
		free(path_cmd);
	}
	return (free(tmp_cmd), tab_free(path), NULL);
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
