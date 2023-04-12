/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:27:34 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/12 19:08:23 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	red_loop(t_token *red, t_cmd *cur)
{
	while (red)
	{
		close_before(cur, red->type);
		if (red->type == RIN)
			cur->in = open(red->value, O_RDONLY);
		else if (red->type == ROUT)
			cur->out = open(red->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (red->type == DRIN)
			ft_heredoc(cur, red);
		else if (red->type == DROUT)
			cur->out = open(red->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cur->in == -1 || cur->out == -1)
		{
			perror(red->value);
			break ;
		}
		red = red->next;
	}
}

void	make_red(t_cmd **lst)
{
	t_cmd	*cur;
	t_token	*red;

	cur = *lst;
	while (cur)
	{
		cur->in = -2;
		cur->out = -2;
		red = cur->red;
		red_loop(red, cur);
		cur = cur->next;
	}
}

int	launch_exec(t_cmd **lst)
{
	t_cmd	*cur;
	t_pid	*lst_pid;

	cur = *lst;
	lst_pid = NULL;
	make_red(lst);
	if (!cur->next && !is_builtin_no_child(cur, lst))
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
	unlink(".tmp");
	free_cmd(lst);
	return (0);
}
