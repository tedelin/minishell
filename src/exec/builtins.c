/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 13:47:01 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/03 13:51:31 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_child(t_cmd *cmd)
{
	int	len;

	if (!cmd->arg || !cmd->arg->value)
		return (1);
	len = ft_strlen(cmd->arg->value);
	if (!ft_strncmp(cmd->arg->value, "echo", 4) && len == 4)
		return (ft_echo(cmd), 0);
	else if (!ft_strncmp(cmd->arg->value, "env", 3) && len == 3)
		return (env_cmd(cmd), 0);
	else if (!ft_strncmp(cmd->arg->value, "pwd", 3) && len == 3)
		return (ft_pwd(0), 0);
	return (1);
}

int	is_builtin_no_child(t_cmd *cmd)
{
	int	len;

	if (!cmd->arg || !cmd->arg->value || cmd->next)
		return (1);
	len = ft_strlen(cmd->arg->value);
	if (!ft_strncmp(cmd->arg->value, "cd", 2) && len == 2)
		return (ft_cd(cmd), 0);
	else if (!ft_strncmp(cmd->arg->value, "exit", 4) && len == 4)
		return (ft_exit(cmd), 0);
	else if (!ft_strncmp(cmd->arg->value, "export", 6) && len == 6)
		return (ft_export(cmd), 0);
	else if (!ft_strncmp(cmd->arg->value, "unset", 5) && len == 5)
		return (ft_unset(cmd), 0);
	return (1);
}
