/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:22:33 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/28 17:20:02 by tedelin          ###   ########.fr       */
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
			if (cur->value && cur->type == WORD)
				t_lstadd_back(&cmd->arg, t_lstnew(ft_strdup(cur->value),
						cur->type));
			else if (cur->value && (cur->type == FD || cur->type == LIM))
				t_lstadd_back(&cmd->red, t_lstnew(ft_strdup(cur->value),
						previous->type));
			previous = cur;
			cur = cur->next;
		}
		lstadd_back_cmd(&cmd, lstnew_cmd());
		if (cur)
			cur = cur->next;
	}
	// print_cmd(&cmd); //debug
	return (free_lst(lst), ft_exec(&cmd));
}
