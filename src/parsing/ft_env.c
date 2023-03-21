/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:19:35 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/21 17:21:11 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_build_env(t_env **lst_env, char **env)
{
	while (env && *env)
	{
		lstadd_back_env(lst_env, lstnew_env(ft_strdup(*env)));
		env++;
	}
}

char	*ft_get_env(t_env *env, char *var)
{
	t_env	*cur;
	int		i;

	cur = env;
	while (cur)
	{
		i = 0;
		while (cur->var[i] == var[i] && cur->var[i] != '=' && cur->var[i]
			&& var[i])
			i++;
		if (cur->var[i] == '=' && !var[i])
			return (cur->var + ft_strlen(var) + 1);
		cur = cur->next;
	}
	return (NULL);
}

void	edit_env(t_env **env, char *var)
{
	t_env	*cur;
	int		i;
	int		j;

	i = ft_len_until(var, '=');
	cur = *env;
	while (cur)
	{
		j = ft_len_until(cur->var, '=');
		if (!ft_strncmp(var, cur->var, i) && i == j)
		{
			cur->var = var;
			return ;
		}
		cur = cur->next;
	}
}

void append_env(t_env **env, char *name)
{
	t_env	*cur;
	char	*to_add;
	int		i;
	int		j;

	
	i = ft_len_until(name, '+');
	cur = *env;
	to_add = ft_strchr(name, '=') + 1;
	while (cur)
	{
		j = ft_len_until(name, '=');
		if (!ft_strncmp(name, cur->var, i) && i == j)
		{
			cur->var = ft_strjoin(cur->var, to_add, 1);
			return ;
		}
		cur = cur->next;
	}
	printf("export: not valid in this context: %s\n", name);
}

void	ft_del(t_env **env, char *name)
{
	t_env	*cur;
	t_env	*prev;

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
		lstadd_back_env(&envp, lstnew_env(ft_strdup(var)));
	if (var && opt == APPEND)
		append_env(&envp, var);
	if (var && opt == EDIT)
		edit_env(&envp, var);
	if (var && opt == DEL)
		ft_del(&envp, var);
	if (opt == FREE)
		return (free_env(&envp), NULL);
	if (opt == PRINT)
		return (print_env(&envp), NULL);
	return (NULL);
}
