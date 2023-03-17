/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:41:46 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/17 16:44:13 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char *opt, char **args)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (opt && ft_strncmp(opt, "-n", 2) == 0)
		n = 1;
	while (args && args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
}
