/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:25:01 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/11 16:09:48 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit = 0;

int	ft_loop(int error)
{
	char	*input;
	t_token	*lst;

	while (1)
	{
		ft_signal(DEFAULT);
		input = readline("minishell$ ");
		if (input && input[0])
		{
			lst = NULL;
			add_history(input);
			error = make_token(&lst, input);
		}
		if (!input)
			return (rl_clear_history(), ft_env(NULL, FREE, NULL, NULL), \
				printf("exit\n"), 0);
		if (error == 1)
			printf("Parse Error\n");
		else if (error == 2)
			return (rl_clear_history(), printf("Malloc fail\n"),
				ft_env(NULL, FREE, NULL, NULL), 2);
		free(input);
	}
	return (ft_env(NULL, FREE, NULL, NULL), rl_clear_history(), 0);
}

int	main(int ac, char **av, char **env)
{
	if (ac > 1 && av)
		return (printf("Usage: ./minishell\n"), 1);
	ft_env(env, INIT, NULL, NULL);
	rl_outstream = stderr;
	return (ft_loop(0));
}
