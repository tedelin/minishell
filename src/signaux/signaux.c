/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 20:29:14 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/10 14:57:52 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sig_int(int sig)
{
    (void) sig;
    write(2, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void	cmd_sigint(int sig)
{
	(void) sig;
	ft_putchar_fd('\n', 2);
}

void    cmd_core_dump(int sig)
{
    (void) sig;
    write(2, "Quit (core dumped)\n", 19);
}

void    ft_signal(int opt)
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
}
