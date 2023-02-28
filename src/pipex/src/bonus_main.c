/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 16:10:59 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/13 17:19:05 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;
	t_pid	*pid;
	t_pid	*head;

	init_data(&data, ac, av, env);
	pid = NULL;
	while (++data.nb_cmd <= ac - 2)
	{
		ft_process(&data, &pid);
	}
	head = pid;
	while (pid)
	{
		waitpid(pid->content, &data.status, 0);
		pid = pid->next;
	}
	if (data.here_doc == 1)
	{
		unlink("tmpfile.txt");
	}
	errno = WEXITSTATUS(data.status);
	ft_exit(&data, &head, "main");
}
