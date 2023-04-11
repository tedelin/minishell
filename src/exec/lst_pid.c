/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:12:25 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/11 16:09:30 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pid	*pid_lstnew(pid_t content)
{
	t_pid	*tmp;

	tmp = malloc(sizeof(t_pid));
	if (tmp)
	{
		tmp->content = content;
		tmp->next = NULL;
	}
	return (tmp);
}

t_pid	*pid_lstlast(t_pid *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

void	pid_lstadd_back(t_pid **lst, t_pid *new)
{
	t_pid	*last;

	if (!*lst)
		*lst = new;
	else
	{
		last = pid_lstlast(*lst);
		last->next = new;
	}
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
