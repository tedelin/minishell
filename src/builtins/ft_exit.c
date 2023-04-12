/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:41:41 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/12 15:25:24 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_free(t_cmd **lst, char *s, int state)
{
	if (s && (state == 2 || state == 0))
		printf("exit\nexit: %s: numeric argument required\n", s);
	else
		printf("exit\n");
	free_cmd(lst);
	ft_env(NULL, FREE, NULL, NULL);
	rl_clear_history();
	exit(state);
}

void	ft_exit(t_cmd *cmd, t_cmd **lst_cmd)
{
	t_token	*tmp;
	int		i;

	if (cmd->arg && !cmd->arg->next && !ft_strncmp(cmd->arg->value, "exit", 4))
		ft_exit_free(lst_cmd, NULL, 0);
	tmp = cmd->arg->next;
	if (tmp && tmp->value)
	{
		i = 0;
		if (!ft_isdigit(tmp->value[i]) \
			&& tmp->value[i] != '-' && tmp->value[i] != '+')
			ft_exit_free(lst_cmd, tmp->value, 2);
		while (tmp->value[++i])
		{
			if (!ft_isdigit(tmp->value[i]))
				ft_exit_free(lst_cmd, tmp->value, 2);
		}
		if (!tmp->next)
			ft_exit_free(lst_cmd, NULL,
				(unsigned int)ft_atoi(tmp->value) % 256);
		printf("exit\nexit: too many arguments\n");
		g_exit = 1;
		return ;
	}
	g_exit = 0;
}
