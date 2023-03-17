/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 13:27:33 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/17 16:50:17 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     is_already(t_env *env, char *new)
{
    int i;

    i = -1;
    while(new[++i] != '=');
    while(env)
    {
        if(ft_strncmp(new, env->var, i + 1) == 0)
        {
            env->var = new;
            return(0);
        }
        env = env->next;
    }
    return(1);
}

void	ft_export(char *name)
{
	t_env	*new;
    t_env *env;
    
    if (!name)
        return ;
    env = ft_get_env(NULL, 1);
	new = lstnew_env(name);
    if(is_already(env, new->var) == 1)
        lstadd_back_env(&env, new);
}

// int main(int ac, char **av, char **env)
// {
//     ft_get_env(env, 0);
//     t_env *l_env = ft_get_env(NULL, 1); 
//     ft_export("TEST_=\"LS\"");
//     // ft_export("TEST_=\"LA\"");
//     ft_export("test=\"LA\"");
//     // ft_export("PATH=\"NON\"");
//     // while (l_env)
//     // {
//     //     printf("%s\n", l_env->var);
//     //     l_env = l_env->next;
//     // }
//     ft_get_env(NULL, 2);
// }