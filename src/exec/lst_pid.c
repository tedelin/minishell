/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 17:12:25 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/12 17:22:31 by tedelin          ###   ########.fr       */
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

void	pid_free(t_pid **lst)
{
	t_pid	*tmp;

	while (lst && *lst)
	{
		tmp = *lst;
		(*lst) = (*lst)->next;
		free(tmp);
	}
}
