/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:59 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/13 14:11:17 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	pid_t	first;

	ft_memset(&data, 0, sizeof(t_data));
	init_data(&data, ac, av, env);
	ft_process(&data);
	data.nb_cmd++;
	first = data.pid;
	ft_process(&data);
	waitpid(first, &data.status, 0);
	waitpid(data.pid, &data.status, 0);
	errno = WEXITSTATUS(data.status);
	ft_exit(&data, "main");
}
