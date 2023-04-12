/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:14:33 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/12 19:11:05 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_loop(t_cmd *cmd, t_token *red, int *cpy)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!line || (ft_strncmp(red->value, line,
					ft_strlen(red->value)) == 0
				&& (ft_strlen(line) == ft_strlen(red->value)))
			|| g_exit == 130)
		{
			if (g_exit == 0 && !line)
				ft_fprintf(2, "minishell: warning: %s (wanted `%s')\n", \
					"here-document delimited by end-of-file", red->value);
			free(line);
			dup2(*cpy, 0);
			break ;
		}
		if (ft_strchr(line, '$'))
			line = ft_dollar(line, 2);
		ft_putendl_fd(line, cmd->in);
		free(line);
	}
}

void	ft_heredoc(t_cmd *cmd, t_token *red)
{
	int		cpy;

	cpy = dup(0);
	cmd->in = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (cmd->in == -1)
		return ;
	ft_signal(HERE_DOC);
	heredoc_loop(cmd, red, &cpy);
	close(cmd->in);
	close(cpy);
	if (g_exit == 130)
		cmd->in = open("/dev/null", O_RDONLY);
	else
		cmd->in = open(".tmp", O_RDONLY);
}
