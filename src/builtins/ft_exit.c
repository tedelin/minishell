/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:41:41 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/22 14:10:44 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_cmd *cmd)
{
	t_token	*tmp;
	int		i;

	if (cmd->arg && !cmd->arg->next && !ft_strncmp(cmd->arg->value, "exit", 4))
		exit(0);
	tmp = cmd->arg->next;
	if (tmp->value)
	{
		i = 0;
		if (!ft_isdigit(tmp->value[i]) && tmp->value[i] != '-'
			&& tmp->value[i] != '+')
			return (printf("exit: %s: numeric argument required\n", tmp->value),
				exit(2), 1);
		while (tmp->value[++i])
		{
			if (!ft_isdigit(tmp->value[i]))
				return (printf("exit: %s: numeric argument required\n",
						tmp->value), exit(2), 1);
		}
		if (!tmp->next)
			exit((unsigned int)ft_atoi(tmp->value) % 256);
		printf("exit: too many arguments\n");
	}
	return (0);
}

// int	main(int ac, char **av)
// {
// 	t_cmd	*cmd;

// 	(void) ac;
// 	lstadd_back_cmd(&cmd, lstnew_cmd());
// 	t_lstadd_back(&cmd->arg, t_lstnew("exit", 0));
// 	// t_lstadd_back(&cmd->arg, t_lstnew("abc", 0));
// 	// t_lstadd_back(&cmd->arg, t_lstnew("4", 0));
// 	ft_exit(cmd);
// }