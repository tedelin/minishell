/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:15:04 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/21 10:50:19 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_add(char *s)
{
	int	i;
	
	if (!s)
		return (0);
	if (!ft_strchr(s, '='))
		return (0);
	i = -1;
	while (s[++i])
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
	}
	return (1);
}

void	ft_export(t_cmd *cmd)
{
	t_token *arg;

	arg = cmd->arg;
	while (arg)
	{
		if (check_add(arg->value))
			ft_env(NULL, ADD, arg->value);
		arg = arg->next;
	}
}