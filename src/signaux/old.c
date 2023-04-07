/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:05:41 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/07 14:22:04 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void signal_handler_child(int sig) {
    if (sig == SIGINT) {
        write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
    } else if (sig == SIGQUIT) {
        printf("\nType CTRL+D to exit\n");
    } else if (sig == SIGTSTP) {
        printf("\nType 'exit' to quit\n");
    }
}

void signal_handler_parent(int sig) {
    if (sig == SIGINT) {
        write(2, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
    } else if (sig == SIGQUIT) {
        printf("\nType CTRL+D to exit\n");
    } else if (sig == SIGTSTP) {
        printf("\nType 'exit' to quit\n");
    }
}


void	set_sign(int ign, int child)
{
	struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
	if (child == 1)
  		sa.sa_handler = signal_handler_child;
	else
		sa.sa_handler = signal_handler_parent;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);
	// if (opt == 0)
	// 	sa.sa_handler = sigint_handler;
	// else
	// 	sa.sa_handler = SIG_IGN;
	// sigemptyset(&sa.sa_mask);
	// sa.sa_flags = 0;
	// sigaction(SIGINT, &sa, NULL);
	// sa.sa_handler = SIG_IGN;
	// sigaction(SIGQUIT, &sa, NULL);
}
