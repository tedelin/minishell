/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:41:46 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/10 15:31:15 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	oldpwd(void)
{
	char	*pwd_join;
	char	*pwd;

	pwd = ft_pwd(1);
	pwd_join = ft_strjoin("OLDPWD=", pwd, 2);
	ft_env(NULL, EDIT, pwd_join, NULL);
}

void	pwd(void)
{
	char	*pwd_join;
	char	*pwd;

	pwd = ft_pwd(1);
	pwd_join = ft_strjoin("PWD=", pwd, 2);
	ft_env(NULL, EDIT, pwd_join, NULL);
}

int	cd_size(t_cmd *cmd)
{
	char	*res;

	res = NULL;
	if (t_lstsize(&cmd->arg) > 2)
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	if (t_lstsize(&cmd->arg) == 1)
	{
		oldpwd();
		ft_env(NULL, GET, "HOME", &res);
		if (res == NULL)
		{
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
		ft_env(NULL, GET, "HOME", &res);
		chdir(res);
		pwd();
		free(res);
		return (1);
	}
	return (0);
}

void	ft_cd(t_cmd *cmd)
{
	char	*res;
	int		i;

	res = NULL;
	if (!cd_size(cmd))
	{
		i = chdir(cmd->arg->next->value);
		if (i == 0)
		{
			ft_env(NULL, GET, "PWD", &res);
			chdir(res);
			free(res);
			oldpwd();
			chdir(cmd->arg->next->value);
			pwd();
			return ;
		}
		printf("minishell: cd: %s: No such file or directory\n",
			cmd->arg->next->value);
		g_exit = 1;
		return ;
	}
	g_exit = 1;
}
