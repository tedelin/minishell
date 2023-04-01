/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:45:33 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/01 13:29:17 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*lstnew_env(char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = value;
	new->next = NULL;
	return (new);
}

void	print_env(t_env **lst)
{
	t_env	*cur;

	cur = *lst;
	while (cur)
	{
		printf("%s\n", cur->var);
		cur = cur->next;
	}
}

void	free_env(t_env **lst)
{
	t_env	*tmp;

	while ((*lst))
	{
		tmp = (*lst);
		(*lst) = (*lst)->next;
		free(tmp->var);
		free(tmp);
	}
}

int	env_lstsize(t_env **lst)
{
	int		i;
	t_env	*temp;

	temp = *lst;
	if (!temp)
		return (0);
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
