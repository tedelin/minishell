/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:42:47 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/22 09:43:48 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwd(int opt)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (opt == 1)
		return (pwd);
	printf("%s\n", pwd);
	free(pwd);
	return (NULL);
}
