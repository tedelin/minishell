/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:19:35 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/17 17:05:32 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_build_env(t_env **lst_env, char **env)
{
	while (env && *env)
	{
		lstadd_back_env(lst_env, lstnew_env(*env));
		env++;
	}
}

t_env *ft_get_env(char **env, int opt, char *var)
{
	static t_env *envp = NULL;

	if (opt == INIT)
		ft_build_env(&envp, env);
	if (opt == GET && var)
	{
		
	}
	if (opt == SET)
	if (opt == 2)
	{
		free_env(&envp);
		envp = NULL;
		return (NULL);
	}
	return (NULL);
}

// t_env **ft_new_env(char **env, int get)
// {
// 	static t_env *envp = NULL;

// 	if (get == 1)
// 		return (&envp);
// 	if (get == 2)
// 	{
// 		free_env(&envp);
// 		envp = NULL;
// 		return (NULL);
// 	}
// 	ft_build_env(&envp, env);
// 	return (NULL);
// }
