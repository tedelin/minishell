/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:19:35 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/17 18:08:22 by tedelin          ###   ########.fr       */
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

char	*ft_get_env(t_env *env, char *var)
{
	t_env	*cur;

	cur = env;
	while (cur)
	{
		if (ft_strncmp(cur->var, var, ft_strlen(var)) == 0)
			return (cur->var + ft_strlen(var) + 1);
		cur = cur->next;
	}
	return (NULL);
}

void	edit_env(t_env **env, char *var)
{
	t_env	*cur;
	int		i;

	i = -1;
	cur = *env;
	while (var && var[++i] != '=')
		;
	while (cur)
	{
		if (!ft_strncmp(var, cur->var, i + 1))
			cur->var = var;
		cur = cur->next;
	}
}

void	ft_del(t_env **env, char *name)
{
	t_env *cur;
	t_env *prev;

	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (!ft_strncmp(cur->var, name, ft_strlen(name)))
		{
			if (prev)
				prev->next = cur->next;
			else
				cur = cur->next;
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

char	*ft_env(char **env, int opt, char *var)
{
	static t_env	*envp = NULL;
	
	if (opt == INIT)
		ft_build_env(&envp, env);
	if (var && opt == GET)
		return (ft_get_env(envp, var));
	if (var && opt == ADD)
		lstadd_back_env(&envp, lstnew_env(var));
	if (var && opt == EDIT)
		edit_env(&envp, var);
	if (var && opt == DEL)
		ft_del(&envp, var);
	if (opt == FREE)
		return (free_env(&envp), NULL);
	if (opt == 10)
		return (print_env(&envp), NULL);
	return (NULL);
}
