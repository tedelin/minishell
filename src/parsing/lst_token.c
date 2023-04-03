/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:39:51 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/03 14:08:59 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*t_lstnew(char *value, int type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	t_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

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

void	free_lst(t_token **lst)
{
	t_token	*tmp;

	while ((*lst))
	{
		tmp = (*lst);
		(*lst) = (*lst)->next;
		free(tmp->value);
		free(tmp);
	}
}

void	print_lst(t_token **lst)
{
	t_token	*cur;

	cur = *lst;
	while (cur)
	{
		printf("value:%s, type:%d\n", cur->value, cur->type);
		cur = cur->next;
	}
}

int	t_lstsize(t_token **lst)
{
	int		i;
	t_token	*temp;

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
