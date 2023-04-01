/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:41:46 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/01 18:22:20 by tedelin          ###   ########.fr       */
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
		ft_env(NULL, GET, "HOME", res);
		if (res == NULL)
		{
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
		ft_env(NULL, GET, "HOME", NULL);
		chdir(res);
		pwd();
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
			ft_env(NULL, GET, "OLDPWD", res);
			chdir(res);
			oldpwd();
			chdir(cmd->arg->next->value);
			pwd();
			return ;
		}
		printf("minishell: cd: %s: No such file or directory\n",
			cmd->arg->next->value);
	}
}

// int main(int ac, char **av, char **env)
// {
//     t_cmd	*cmd;

//     ft_env(env, INIT, NULL);
//     lstadd_back_cmd(&cmd, lstnew_cmd());
// 	t_lstadd_back(&cmd->arg, t_lstnew("cd", 0));
// 	t_lstadd_back(&cmd->arg, t_lstnew("../../../..", 0));
// 	// t_lstadd_back(&cmd->arg, t_lstnew("sa", 0));
//     // ft_env(NULL, EDIT, "PWD=environnement");
//     ft_cd(cmd);
//     ft_pwd(0);
//     // ft_env(NULL, PRINT, NULL);
// }