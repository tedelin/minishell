/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:50:20 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/22 18:40:18 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	init_data(t_data *data, int ac, char **av, char **env)
{
	if (ac < 5)
	{
		ft_putstr_fd("Error : Expected at least 4 arguments\n", 2);
		exit(1);
	}
	ft_memset(data, 0, sizeof(t_data));
	data->env = env;
	data->av = av;
	data->ac = ac;
	data->nb_cmd = 1;
	ft_heredoc(data, ac, av);
	if (data->here_doc == 1)
	{
		close(data->in);
		data->in = open("tmpfile.txt", O_RDONLY);
		data->out = open(av[ac - 1], O_APPEND | O_WRONLY | O_CREAT, 0664);
		data->nb_cmd++;
	}
	else
	{
		data->in = open(av[1], O_RDONLY);
		data->out = open(av[ac - 1], O_TRUNC | O_WRONLY | O_CREAT, 0664);
	}
	data->path = ft_path(env);
}

void	ft_heredoc(t_data *data, int ac, char **av)
{
	char	*line;

	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
		{
			ft_putstr_fd("Error : Expected at least 5 arguments\n", 2);
			exit(1);
		}
		data->in = open("tmpfile.txt", O_CREAT | O_WRONLY, 0664);
		while (1)
		{
			ft_putstr_fd("pipe heredoc>", 0);
			line = get_next_line(0);
			if (!line || (ft_strncmp(av[2], line, ft_strlen(av[2])) == 0
					&& (ft_strlen(line) - 1 == ft_strlen(av[2]))))
			{
				free(line);
				break ;
			}
			ft_putstr_fd(line, data->in);
			free(line);
		}
		data->here_doc = 1;
	}
}

void	free_split(char	**tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_exit(t_data *data, t_pid **lst_pid, char *msg)
{
	t_pid	*tmp;

	while ((*lst_pid))
	{
		tmp = (*lst_pid);
		(*lst_pid) = (*lst_pid)->next;
		free(tmp);
		tmp = NULL;
	}
	free(*lst_pid);
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
