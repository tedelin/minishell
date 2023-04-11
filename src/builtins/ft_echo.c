/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:41:46 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/11 15:48:57 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_line(t_token **arg, int n)
{
	int		i;

	while (*arg)
	{
		i = 1;
		while ((*arg)->value[i] && (*arg)->value[i] == 'n')
			i++;
		if (!(*arg)->value[i] && i > 1)
		{
			n++;
			(*arg) = (*arg)->next;
		}
		else
			break ;
	}
	return (n);
}

void	ft_echo(t_cmd *cmd)
{
	t_token	*arg;
	int		n;

	n = 0;
	if (!cmd->arg->next)
	{
		printf("\n");
		return ;
	}
	arg = cmd->arg->next;
	if (!ft_strncmp(arg->value, "-n", 2))
		n = new_line(&arg, n);
	while (arg)
	{
		ft_putstr_fd(arg->value, 1);
		arg = arg->next;
		if (arg)
			ft_putstr_fd(" ", 1);
	}
	if (n == 0)
		ft_putstr_fd("\n", 1);
}
