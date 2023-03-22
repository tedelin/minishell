/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:41:46 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/22 13:17:54 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    oldpwd()
{
    char    *pwd_join;
    char    *pwd;
    
    pwd = ft_pwd(1);
    pwd_join = ft_strjoin("OLDPWD=", pwd, 2);
    ft_env(NULL, EDIT, pwd_join);
}

void    pwd()
{
    char    *pwd_join;
    char    *pwd;
    
    pwd = ft_pwd(1);
    pwd_join = ft_strjoin("PWD=", pwd, 2);
    ft_env(NULL, EDIT, pwd_join);
}

void    ft_cd(t_cmd *cmd)
{
    int i;
    
    if (t_lstsize(&cmd->arg) > 2)
    {
        printf("minishell: cd: too many arguments\n");
        return ;
    }
    if(t_lstsize(&cmd->arg) == 1)
    {
        ft_pwd(0);
        oldpwd();
        if(ft_env(NULL, GET, "HOME") == NULL)
        {
            printf("minishell: cd: HOME not set\n");
            return ;
        }
        chdir(ft_env(NULL, GET, "HOME"));
        pwd();
        ft_pwd(0);
        return ;
    }
    i = chdir(cmd->arg->next->value);
    if(i == 0)
    {
        chdir(ft_env(NULL, GET, "OLDPWD"));
        oldpwd();
        chdir(cmd->arg->next->value);
        pwd();
        ft_pwd(0);
        return;
    }
    printf("minishell: cd: %s: No such file or directory\n", cmd->arg->next->value);
}

int main(int ac, char **av, char **env)
{
    t_cmd	*cmd;
    
    ft_env(env, INIT, NULL);
    lstadd_back_cmd(&cmd, lstnew_cmd());
	t_lstadd_back(&cmd->arg, t_lstnew("cd", 0));
	t_lstadd_back(&cmd->arg, t_lstnew("~", 0));
	// t_lstadd_back(&cmd->arg, t_lstnew(av[2], 0));
    // ft_env(NULL, EDIT, "PWD=environnement");
    ft_cd(cmd);
    // ft_env(NULL, PRINT, NULL);
}