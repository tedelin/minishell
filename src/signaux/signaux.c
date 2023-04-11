/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:29:14 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/11 09:34:22 by mcatal-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sig_here_doc(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		write(2, "\n", 1);
		g_exit = 130;
	}
}

void	sig_int(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	cmd_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 2);
}

void	cmd_core_dump(int sig)
{
	(void)sig;
	write(2, "Quit (core dumped)\n", 19);
}

void	ft_signal(int opt)
{
	if (opt == IGNORE)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (opt == DEFAULT)
	{
		signal(SIGINT, sig_int);
		signal(SIGQUIT, SIG_IGN);
	}
	if (opt == CHILD)
	{
		signal(SIGINT, cmd_sigint);
		signal(SIGQUIT, cmd_core_dump);
	}
	if (opt == HERE_DOC)
	{
		signal(SIGINT, sig_here_doc);
		signal(SIGQUIT, SIG_IGN);
	}
}
