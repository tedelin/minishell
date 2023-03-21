/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:22:33 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/21 17:07:05 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_cmd(t_token **lst)
{
	t_cmd	*cmd;
	t_token	*previous;
	t_token	*cur;

	cmd = lstnew_cmd();
	cur = *lst;
	previous = NULL;
	while (cur)
	{
		while (cur && cur->type != PIPE)
		{
			if (cur->type == WORD)
				t_lstadd_back(&cmd->arg, t_lstnew(ft_strdup(cur->value),
						cur->type));
			else if (cur->type == FD)
				t_lstadd_back(&cmd->red, t_lstnew(ft_strdup(cur->value),
						previous->type));
			previous = cur;
			cur = cur->next;
		}
		lstadd_back_cmd(&cmd, lstnew_cmd());
		if (cur)
			cur = cur->next;
	}
	print_cmd(&cmd); //debug
	return (free_lst(lst), free_cmd(&cmd), 0);
}

