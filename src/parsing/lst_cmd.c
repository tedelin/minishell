/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 13:24:01 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/20 14:09:03 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

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

t_cmd	*lstnew_cmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(t_cmd));
	return (new);
}

void	print_cmd(t_cmd **lst)
{
	t_cmd	*cur;
	t_token *tmp_arg;
	t_token *tmp_red;

	cur = *lst;
	tmp_arg = cur->arg;
	tmp_red = cur->red;
	while (cur)
	{
		while (tmp_arg)
		{
			printf("arg->value : %s\n", tmp_arg->value);
       		printf("arg->type : %u\n", tmp_arg->type);
			tmp_arg = tmp_arg->next;
		}
        printf("---------------\n");
        while(tmp_red)
        {
            printf("red->value : %s\nred->type : %u\n", tmp_red->value, tmp_red->type);
		    tmp_red = tmp_red->next;
        }
		cur = cur->next;
	}
}

void	free_cmd(t_cmd **lst)
{
	t_cmd	*tmp;

	while ((*lst))
	{
		tmp = (*lst);
		(*lst) = (*lst)->next;
        free_lst(&tmp->arg);
        free_lst(&tmp->red);
		free(tmp);
	}
}
