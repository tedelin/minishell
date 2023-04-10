/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:15:04 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/10 15:31:09 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_add(char *s)
{
	int	i;

	if (!s || !ft_isalpha(s[0]) || !ft_strchr(s, '='))
		return (0);
	i = -1;
	while (s[++i] && s[i] != '=')
	{
		if (s[i] == '+' && s[i + 1] != '=')
			return (0);
		else if (s[i] == '+' && s[i + 1] == '=')
			return (2);
		if (!ft_isalnum(s[i]) && s[i] != '_')
			return (0);
	}
	return (1);
}

void	ft_export(t_cmd *cmd)
{
	t_token	*arg;

	if (!cmd->arg || !cmd->arg->next)
		return ;
	arg = cmd->arg->next;
	while (arg)
	{
		if (check_add(arg->value) == 1)
			ft_env(NULL, EDIT, ft_strdup(arg->value), NULL);
		else if (check_add(arg->value) == 2)
			ft_env(NULL, APPEND, arg->value, NULL);
		else
			printf("minishell: export: `%s': not a valid identifier\n",
				arg->value);
		arg = arg->next;
	}
}
