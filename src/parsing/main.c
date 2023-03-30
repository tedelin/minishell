/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:09:48 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/30 16:30:04 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	int		error;
	t_token	*lst;

	(void)ac;
	(void)av;
	ft_env(env, INIT, NULL, NULL);
	// whle(1)
	rl_outstream = stderr;
	int i = 0;
	while (1)
	{
		input = readline("minishell>");
		// input = get_next_line(0);
		// input = "ls | wc -l";
		// if (!input)
		// 	return (1);
		lst = NULL;
		add_history(input);
		error = make_token(&lst, input);
		if (error == 1)
			return (printf("Parse Error\n"), 0);
		else if (error == 2)
			return (printf("Malloc failed\n"), ft_env(NULL, FREE, NULL, NULL), 2);
		// free(input);
		// fflush(stdout);
		i++;
		// fprintf(stderr, "\n\n");
	}
	ft_env(NULL, FREE, NULL, NULL);
}
