/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:09:37 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/12 14:29:55 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_cmd *cmd)
{
	t_token	*cur_arg;

	if (cmd->arg && cmd->arg->next)
	{
		cur_arg = cmd->arg->next;
		while (cur_arg)
		{
			ft_env(NULL, DEL, cur_arg->value, NULL);
			cur_arg = cur_arg->next;
		}
	}
}
