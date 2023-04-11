/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:09:37 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/11 17:20:38 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_cmd *cmd)
{
	if (cmd->arg && cmd->arg->next)
	{
		cmd->arg = cmd->arg->next;
		while (cmd->arg)
		{
			ft_env(NULL, DEL, cmd->arg->value, NULL);
			cmd->arg = cmd->arg->next;
		}
	}
}
