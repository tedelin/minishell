/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:22:33 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/01 13:39:59 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_arg_and_red(t_token *cur, t_cmd *lst_cmd)
{
	t_token	*previous;

	previous = NULL;
	while (cur && cur->type != PIPE)
	{
		if (cur->value && cur->type == WORD)
			t_lstadd_back(&lst_cmd->arg, t_lstnew(ft_strdup(cur->value),
					cur->type));
		else if (cur->value && (cur->type == FD || cur->type == LIM))
			t_lstadd_back(&lst_cmd->red, t_lstnew(ft_strdup(cur->value),
					previous->type));
		previous = cur;
		cur = cur->next;
	}
	return (cur);
}

int	build_cmd(t_token **lst)
{
	t_cmd	*cmd;
	t_cmd	*head;
	t_token	*cur;

	cmd = lstnew_cmd();
	cur = *lst;
	head = cmd;
	while (cur)
	{
		cur = ft_arg_and_red(cur, cmd);
		if (cur)
		{
			lstadd_back_cmd(&cmd, lstnew_cmd());
			cur = cur->next;
		}
		cmd = cmd->next;
	}
	cmd = head;
	return (free_lst(lst), launch_exec(&cmd));
}
	// print_cmd(&cmd); //debug
