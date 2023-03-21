/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:41:46 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/21 11:16:55 by tedelin          ###   ########.fr       */
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
	if (!cmd->arg->next)
		return;
	arg = cmd->arg->next;
	if (!ft_strncmp(arg->value, "-n", 2))
	{
		while (arg->value[i] && arg->value[i] == 'n')
			i++;
		if (!arg->value[i] && n++)
			arg = arg->next;
	}
	while (arg)
	{
		if (ft_strncmp(arg->value, "-n", 2)
			|| (!ft_strncmp(arg->value, "-n", 2) && arg->value[2]))
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
	// t_lstadd_back(&cmd->arg, t_lstnew("-n", 0));
	t_lstadd_back(&cmd->arg, t_lstnew("-ne", 0));
	t_lstadd_back(&cmd->arg, t_lstnew("premier", 0));
	t_lstadd_back(&cmd->arg, t_lstnew("deuxieme", 0));
	t_lstadd_back(&cmd->arg, t_lstnew("troisieme", 0));
	ft_echo(cmd);
}