/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:23:55 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/03 13:48:13 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_cmd *cmd)
{
	char	*line;

	cmd->in = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (cmd->in == -1)
		return ;
	while (1)
	{
		line = readline(">");
		if (!line || (ft_strncmp(cmd->red->value, line,
					ft_strlen(cmd->red->value)) == 0
				&& (ft_strlen(line) == ft_strlen(cmd->red->value))))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, cmd->in);
		free(line);
	}
	close(cmd->in);
	cmd->in = open(".tmp", O_RDONLY);
}

void	close_before(t_cmd *cmd, int type)
{
	if (type == RIN && cmd->in > 2)
		close(cmd->in);
	else if (type == ROUT && cmd->out > 2)
		close(cmd->out);
	else if (type == DRIN && cmd->in > 2)
		close(cmd->in);
	else if (type == DROUT && cmd->out > 2)
		close(cmd->out);
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
			close_before(cur, cur->red->type);
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
			if (cur->in == -1 || cur->out == -1)
			{
				perror(cur->red->value);
				break ;
			}
			cur->red = cur->red->next;
		}
		cur = cur->next;
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
	if (!cur->next && !is_builtin_no_child(cur))
	{
		free_cmd(lst);
		return (0);
	}
	while (cur)
	{
		ft_process(cur, &lst_pid, lst);
		cur = cur->next;
	}
	ft_wait(lst_pid);
	free_cmd(lst);
	return (0);
}
