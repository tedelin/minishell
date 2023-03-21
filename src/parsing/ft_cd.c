/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:41:46 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/21 16:48:48 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_cd()//t_cmd *cmd)
{
    char *pwd;
    //sans verif
    ft_pwd();
    pwd = ft_strjoin("OLDPWD=", "ancien", 0);//ft_pwd())
    ft_env(NULL, EDIT, pwd);
    chdir("../test");
    ft_pwd();
}

// int main()
// {
//     ft_cd();
// }