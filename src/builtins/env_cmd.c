/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:41:25 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/29 15:07:30 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(t_cmd *cmd)
{
	if (!cmd || !cmd->arg)
		return ;
	if (t_lstsize(&cmd->arg) != 1)
		printf("env: too many arguments\n");
	else if (cmd->arg && !ft_strncmp(cmd->arg->value, "env", 3)
		&& ft_strlen(cmd->arg->value) == 3)
		ft_env(NULL, PRINT, NULL, NULL);
}
