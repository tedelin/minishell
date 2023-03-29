/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 15:57:57 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/29 17:29:48 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_process(t_cmd *cmd, t_pid **lst_pid)
{
	pid_t	pid;
	int tab_fd[2];

    
	if (pipe(tab_fd) == -1)
		exit_child(cmd, lst_pid, "pipe ");
    cmd->out = tab_fd[0];
	if (cmd->next)
    	cmd->next->in = tab_fd[1];
	else
		cmd->in = STDIN_FILENO;
	pid = fork();
	if (pid == -1)
		exit_child(cmd, lst_pid, "pid ");
	if (pid == 0)
		ft_child(cmd, lst_pid);
	else
	{
		pid_lstadd_back(lst_pid, pid_lstnew(pid));
		// close (cmd->out);
		// close(cmd->in);
	}
}

void	ft_child(t_cmd *cmd, t_pid **lst_pid)
{
    
    // printf("fds is [0]:%d    [1]:%d\n", cmd->fd[0], cmd->fd[1]);
	dup2(cmd->out, STDOUT_FILENO);
    dup2(cmd->in, STDIN_FILENO);
	// if (!cmd->next)
	// {
	// 	if (cmd->in == -1)
	// 		exit_child(cmd, lst_pid, NULL);
	// 	else if (cmd->in != -2)
	// 		dup2(cmd->in, STDIN_FILENO);
	// 	else
	// 	{
	// 		fprintf(stderr, "FD[0]: %d\n", cmd->in);
	// 		dup2(cmd->in, STDIN_FILENO);
	// 	}
	// 	if (cmd->out == -1)
	// 		exit_child(cmd, lst_pid, NULL);
	// 	else if (cmd->out != -2)
	// 		dup2(cmd->out, STDOUT_FILENO);
	// }
	// else
	// {
	// 	// fprintf(stderr, "%s\n\n\n", cmd->arg->value);
	// 	if (cmd->in == -1)
	// 		exit_child(cmd, lst_pid, NULL);
	// 	else if (cmd->in != -2)
	// 		dup2(cmd->in, STDIN_FILENO);
	// 	else
	// 		dup2(cmd->in, STDIN_FILENO);
	// 	if (cmd->out == -1)
	// 		exit_child(cmd, lst_pid, NULL);
	// 	if (cmd->out != -2)
	// 		dup2(cmd->out, STDOUT_FILENO);
	// 	else // if (cmd->out != -2)
	// 	{
	// 		fprintf(stderr, "FD[1]: %d\n", cmd->out);	
	// 		dup2(cmd->out, STDOUT_FILENO);
	// 	}
	// }
	// close(cmd->in);
	// close(cmd->out);
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
	(void) lst_pid;
	execve(path, args, env);
	// if (!path || execve(path, args, env) == -1)
	// {
	// 	errno = 127;
	// 	ft_putstr_fd(args[0], 2);
	// 	// ft_putendl_fd(": command not found", 2);
	// 	exit_child(cmd, lst_pid, "main");
	// }
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
	close(cmd->in);
	close(cmd->out);
	exit(errno);
}