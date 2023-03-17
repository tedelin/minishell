/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:27:33 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/17 18:17:10 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char *name)
{
	char *res;
	int len;

	if (!name)
		return ;
	len = -1;
	while (name[++len] && name[len] != '=');
	res = ft_substr(name, 0, len);
	printf("%s\n", res);
	if (ft_env(NULL, GET, res))
		ft_env(NULL, EDIT, name);
	else
		ft_env(NULL, ADD, name);
}

// int main(int ac, char **av, char **env)
// {
//     ft_env(env, 0);
//     t_env *l_env = ft_env(NULL, 1);
//     ft_export("TEST_=\"LS\"");
//     // ft_export("TEST_=\"LA\"");
//     ft_export("test=\"LA\"");
//     // ft_export("PATH=\"NON\"");
//     // while (l_env)
//     // {
//     //     printf("%s\n", l_env->var);
//     //     l_env = l_env->next;
//     // }
//     ft_env(NULL, 2);
// }