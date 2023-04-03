/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:41:46 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/03 11:47:09 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	new_line(t_token **arg, int n)
{
	int		i;

	i = 1;
	while ((*arg)->value[i] && (*arg)->value[i] == 'n')
			i++;
	if (!(*arg)->value[i] && n++)
		*arg = (*arg)->next;
	return (n);
}

void	ft_echo(t_cmd *cmd)
{
	t_token	*arg;
	int		n;

	n = 0;
	if (!cmd->arg->next)
		return ;
	arg = cmd->arg->next;
	if (!ft_strncmp(arg->value, "-n", 2))
		n = new_line(&arg, n);
	while (arg)
	{
		if (ft_strncmp(arg->value, "-n", 2) || (!ft_strncmp(arg->value, "-n", 2)
				&& arg->value[2]))
			ft_putstr_fd(arg->value, 1);
		arg = arg->next;
		if (arg)
			ft_putstr_fd(" ", 1);
	}
	if (n == 0)
		ft_putstr_fd("\n", 1);
}

// int	main(void)
// {
// 	t_cmd	*cmd;

// 	lstadd_back_cmd(&cmd, lstnew_cmd());
// 	t_lstadd_back(&cmd->arg, t_lstnew("echo", 0));
// 	t_lstadd_back(&cmd->arg, t_lstnew("-n", 0));
// 	t_lstadd_back(&cmd->arg, t_lstnew("-ne", 0));
// 	t_lstadd_back(&cmd->arg, t_lstnew("premier", 0));
// 	t_lstadd_back(&cmd->arg, t_lstnew("deuxieme", 0));
// 	t_lstadd_back(&cmd->arg, t_lstnew("troisieme", 0));
// 	ft_echo(cmd);
// }
