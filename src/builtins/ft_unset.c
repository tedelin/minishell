/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:09:37 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/17 15:15:52 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_unset(char *name)
{
	t_env **env;
	t_env *prev;
	
	env = ft_get_env(NULL, 1);
	prev = NULL;
	while (env && *env)
	{
		if (ft_strncmp((*env)->var, name, ft_strlen(name)) == 0)
		{
			free((*env)->var);
			(*env)->var = NULL;
			if (prev)
				prev->next = (*env)->next;
			else
				(*env) = (*env)->next;
			return ;
		}
		prev = (*env);
		(*env) = (*env)->next;
	}
}