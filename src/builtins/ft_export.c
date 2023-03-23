/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 10:15:04 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/23 11:22:21 by tedelin          ###   ########.fr       */
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
		if (s[i] == '_' && s[i + 1] && s[i + 1] == '+')
		{
			i += 2;
			if (s[i] == '=')
				return (2);
			else
				return (0);
		}
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
			ft_env(NULL, ADD, arg->value);
		else if (check_add(arg->value) == 2)
			ft_env(NULL, APPEND, arg->value);
		else
			printf("minishell: export: `%s': not a valid identifier\n",
				arg->value);
		arg = arg->next;
	}
}

// int	main(int ac, char **av, char **env)
// {
// 	t_cmd	*cmd;

// 	ft_env(env, INIT, NULL);
// 	// lstadd_back_cmd(&cmd, lstnew_cmd());
// 	// t_lstadd_back(&cmd->arg, t_lstnew("export", 0));
// 	// t_lstadd_back(&cmd->arg, t_lstnew("TEST____+___=ls", 0));
// 	// t_lstadd_back(&cmd->arg, t_lstnew("1TEST=ls", 0));
// 	// t_lstadd_back(&cmd->arg, t_lstnew("+TEST=ls", 0));
// 	// t_lstadd_back(&cmd->arg, t_lstnew("TEST_+12=test", 0));
// 	// ft_export(cmd);
// 	// ft_env(NULL, ADD, "TEST_=ls");
// 	// ft_env(NULL, EDIT, "PAT=test");
// 	ft_env(NULL, APPEND, "PATHHHH+=test");
// 	// ft_env(NULL, APPEND, "TEST+=test");
// 	ft_env(NULL, PRINT, NULL);
// 	ft_env(NULL, FREE, NULL);
// }
