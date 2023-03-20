/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:41:46 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/20 16:48:10 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_cmd *cmd)
{
	t_token	*arg;
	int		i;
	int		n;

	i = 1;
	n = 0;
	if (cmd->arg->next)
		arg = cmd->arg->next;
	// printf("---%s\n", arg->value);
	if (ft_strncmp(arg->value, "-n", 2) == 0)
	{
		while (arg->value[i] && arg->value[i] == 'n')
			i++;
		if (!arg->value[i])
			n = 1;
		arg = arg->next;
	}
	while (arg)
	{
		ft_putstr_fd(arg->value, 1);
		arg = arg->next;
	}
	if (n == 0)
		ft_putstr_fd("\n", 1);
}

int main()
{
	t_cmd *cmd;

	lstadd_back_cmd(&cmd, lstnew_cmd());
	t_lstadd_back(&cmd->arg, t_lstnew("echo", 0));
	t_lstadd_back(&cmd->arg, t_lstnew("-n", 0));
	t_lstadd_back(&cmd->arg, t_lstnew("premier\n", 0));
	t_lstadd_back(&cmd->arg, t_lstnew("deuxieme", 0));
	ft_echo(cmd);
}