/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <mcatal-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 13:19:35 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/04 16:17:51 by mcatal-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
