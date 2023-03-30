/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:22:33 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/30 14:00:59 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_cmd(t_token **lst)
{
	t_cmd	*cmd;
	t_cmd	*head;
	t_token	*previous;
	t_token	*cur;

	cmd = lstnew_cmd();
	cur = *lst;
	head = cmd;
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
		if (cur)
			lstadd_back_cmd(&cmd, lstnew_cmd());
		if (cur)
			cur = cur->next;
		cmd = cmd->next;
	}
	cmd = head;
	// print_cmd(&cmd); //debug
	return (free_lst(lst), launch_exec(&cmd));
}
