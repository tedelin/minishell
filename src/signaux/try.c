/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:22:49 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/07 14:50:40 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void no_action(int sig)
// {
// 	(void) sig;
// 	return ;
// }

static void default_sigint(int sig)
{
	(void) sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	cmd_sigquit(int sig)
{
	(void) sig;
	return ;
}

static void	sigint_child(int sig)
{
	(void) sig;
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
}

void	cmd_signal_parent(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, cmd_sigquit);
}

void	signal_parent(void)
{
	signal(SIGINT, default_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_child(void)
{
	signal(SIGINT, sigint_child);
	signal(SIGQUIT, SIG_IGN);
}
