/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:19:35 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/04 11:20:33 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_build_env(t_env **lst_env, char **env)
{
	t_env	*tmp;
	char	*add;

	while (env && *env)
	{
		add = ft_strdup(*env);
		if (add)
			tmp = lstnew_env(add);
		else
		{
			free(add);
			return ;
		}
		if (tmp)
			lstadd_back_env(lst_env, tmp);
		else
			return ;
		env++;
	}
}

void	ft_get_env(t_env *env, char *var, char **res)
{
	t_env	*cur;
	int		i;
	int		j;

	cur = env;
	i = ft_strlen(var);
	while (cur)
	{
		j = ft_len_until(cur->var, '=');
		if (!ft_strncmp(var, cur->var, i) && i == j)
		{
			*res = cur->var + i + 1;
			return ;
		}
		cur = cur->next;
	}
}

void	edit_env(t_env **env, char *var)
{
	t_env	*cur;
	int		i;
	int		j;

	if (!var)
		return ;
	i = ft_len_until(var, '=');
	cur = *env;
	while (cur)
	{
		j = ft_len_until(cur->var, '=');
		if (!ft_strncmp(var, cur->var, i) && i == j)
		{
			free(cur->var);
			cur->var = var;
			return ;
		}
		cur = cur->next;
	}
	ft_env(NULL, ADD, var, NULL);
}

void	append_env(t_env **env, char *name)
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
	int		j;
	int		i;

	cur = *env;
	prev = NULL;
	i = ft_strlen(name);
	while (cur)
	{
		j = ft_len_until(cur->var, '=');
		if (!ft_strncmp(cur->var, name, i) && i == j)
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

t_env	*ft_env(char **env, int opt, char *var, char **res)
{
	static t_env	*envp = NULL;

	if (opt == INIT)
		ft_build_env(&envp, env);
	if (var && opt == GET)
		ft_get_env(envp, var, res);
	if (var && opt == ADD)
		lstadd_back_env(&envp, lstnew_env(ft_strdup(var)));
	if (var && opt == APPEND)
		append_env(&envp, var);
	if (var && opt == EDIT)
		edit_env(&envp, var);
	if (var && opt == DEL)
		ft_del(&envp, var);
	if (opt == FREE)
		free_env(&envp);
	if (opt == PRINT)
		print_env(&envp);
	if (opt == LST)
		return (envp);
	return (NULL);
}
