/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:09:48 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/03 15:21:52 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit = 0;

int	main(int ac, char **av, char **env)
{
	char	*input;
	int		error;
	t_token	*lst;

	(void)ac;
	(void)av;
	ft_env(env, INIT, NULL, NULL);
	rl_outstream = stderr;
	while (1)
	{
		input = readline("minishell$ ");
		// input = "ls | wc -l";
		if (!input)
			return (1);
		lst = NULL;
		add_history(input);
		error = make_token(&lst, input);
		if (error == 1)
			printf("Parse Error\n");
			// return (printf("Parse Error\n"), 0);
		else if (error == 2)
			return (printf("Malloc failed\n"), ft_env(NULL, FREE, NULL, NULL), 2);
		free(input);
		// printf("exit status: %d\n", g_exit);
	}
	ft_env(NULL, FREE, NULL, NULL);
}

// int	main(int ac, char **av, char **env)
// {
// 	char	*input;
// 	int		error;
// 	t_token	*lst;

// 	(void)ac;
// 	(void)av;
// 	ft_env(env, INIT, NULL, NULL);
// 	// rl_outstream = stderr;
// 	// while (1)
// 	// {
// 	// 	input = readline("minishell$ ");
// 	input = "< Makefile < Makefile cat | cat | cat | wc -l";
// 	if (!input)
// 		return (1);
// 	lst = NULL;
// 	// add_history(input);
// 	error = make_token(&lst, input);
// 	if (error == 1)
// 		return (printf("Parse Error\n"), 0);
// 	else if (error == 2)
// 		return (printf("Malloc failed\n"), ft_env(NULL, FREE, NULL, NULL), 2);
// // 	free(input);
// 	// }
// 	ft_env(NULL, FREE, NULL, NULL);
// }
