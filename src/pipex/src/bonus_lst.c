/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:12:25 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/09 17:14:32 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
