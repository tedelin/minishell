/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:23:55 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/01 13:28:06 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	int	len;

	if (!cmd->arg || !cmd->arg->value)
		return (1);
	len = ft_strlen(cmd->arg->value);
	if (!ft_strncmp(cmd->arg->value, "cd", 2) && len == 2)
		return (ft_cd(cmd), 0);
	else if (!ft_strncmp(cmd->arg->value, "echo", 4) && len == 4)
		return (ft_echo(cmd), 0);
	else if (!ft_strncmp(cmd->arg->value, "env", 3) && len == 3)
		return (env_cmd(cmd), 0);
	else if (!ft_strncmp(cmd->arg->value, "export", 6) && len == 6)
		return (ft_export(cmd), 0);
	else if (!ft_strncmp(cmd->arg->value, "pwd", 3) && len == 3)
		return (ft_pwd(0), 0);
	else if (!ft_strncmp(cmd->arg->value, "unset", 5) && len == 5)
		return (ft_unset(cmd), 0);
	else if (!ft_strncmp(cmd->arg->value, "exit", 4) && len == 4)
		return (ft_exit(cmd), 0);
	else
		return (1);
}

void	ft_heredoc(t_cmd *cmd)
{
	char	*line;

	cmd->in = open("tmpfile.txt", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	while (1)
	{
		line = readline("pipe heredoc>");
		if (!line || (ft_strncmp(cmd->red->value, line,
					ft_strlen(cmd->red->value)) == 0
				&& (ft_strlen(line) == ft_strlen(cmd->red->value))))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, cmd->in);
		free(line);
	}
}

void	make_red(t_cmd **lst)
{
	t_cmd	*cur;

	cur = *lst;
	while (cur)
	{
		cur->in = -2;
		cur->out = -2;
		while (cur->red)
		{
			if (cur->red->type == RIN)
				cur->in = open(cur->red->value, O_RDONLY);
			else if (cur->red->type == ROUT)
				cur->out = open(cur->red->value, O_WRONLY | O_CREAT | O_TRUNC,
						0644);
			else if (cur->red->type == DRIN)
				ft_heredoc(cur);
			else if (cur->red->type == DROUT)
				cur->out = open(cur->red->value, O_WRONLY | O_CREAT | O_APPEND,
						0644);
			cur->red = cur->red->next;
		}
		cur = cur->next;
	}
}

void	ft_wait(t_pid *lst)
{
	t_pid	*tmp;

	while (lst)
	{
		waitpid(lst->content, NULL, 0);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

int	launch_exec(t_cmd **lst)
{
	t_cmd	*cur;
	char	**cur_arg;
	t_pid	*lst_pid;

	make_red(lst);
	cur = *lst;
	lst_pid = NULL;
	while (cur)
	{
		ft_process(cur, &lst_pid, lst);
		cur = cur->next;
	}
	ft_wait(lst_pid);
	free_cmd(lst);
	return (0);
}
