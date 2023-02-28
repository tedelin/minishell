/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:50:20 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/13 18:11:55 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_data *data, int ac, char **av, char **env)
{
	if (ac != 5)
	{
		ft_putstr_fd("Error : Expected 4 arguments\n", 2);
		exit(1);
	}
	ft_memset(data, 0, sizeof(t_data));
	data->env = env;
	data->av = av;
	data->ac = ac;
	data->nb_cmd = 2;
	data->in = open(av[1], O_RDONLY);
	data->out = open(av[ac - 1], O_TRUNC | O_WRONLY | O_CREAT, 0664);
	data->path = ft_path(env);
}

void	free_split(char	**tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_exit(t_data *data, char *msg)
{
	free_split(data->cmd_args);
	free_split(data->path);
	free(data->cmd);
	free(data->cmd_path);
	if (data->in != -1)
		close(data->in);
	if (data->out != -1)
		close(data->out);
	if (ft_strncmp(msg, "main", 4) == 0)
		exit(errno);
	perror(msg);
	close(data->fd[0]);
	close(data->fd[1]);
	exit(errno);
}
