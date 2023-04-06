/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:25:01 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/06 14:23:33 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit = 0;

int	ft_loop(void)
{
	char	*input;
	int		error;
	t_token	*lst;

	while (1)
	{
		set_sign(0);
		input = readline("minishell$ ");
		if (input && input[0])
		{
			lst = NULL;
			add_history(input);
			error = make_token(&lst, input);
		}
		if (!input)
			return (ft_env(NULL, FREE, NULL, NULL), printf("exit\n"), 0);
		if (error == 1)
			printf("Parse Error\n");
		else if (error == 2)
			return (printf("Malloc fail\n"), ft_env(NULL, FREE, NULL, NULL), 2);
		free(input);
	}
	ft_env(NULL, FREE, NULL, NULL);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	if (ac > 1 && av)
		return (printf("Usage: ./minishell\n"), 1);
	ft_env(env, INIT, NULL, NULL);
	rl_outstream = stderr;
	return (ft_loop());
}

// int	main(int ac, char **av, char **env)
// {
// 	(void) ac;
// 	(void) av;
// 	(void) env;
// 	char *str = malloc(sizeof(char) * 3);
// 	if (!str)
// 		return (1);
// 	return (free(str), 0);
// // 	char	*input;
// // 	int		error;
// // 	t_token	*lst;

// // 	(void)ac;
// // 	(void)av;
// // 	ft_env(env, INIT, NULL, NULL);
// // 	// rl_outstream = stderr;
// // 	// while (1)
// // 	// {
// // 	// 	input = readline("minishell$ ");
// // 	input = "< Makefile | cat | cat | wc -l";
// // 	if (!input)
// // 		return (1);
// // 	lst = NULL;
// // 	// add_history(input);
// // 	error = make_token(&lst, input);
// // 	if (error == 1)
// // 		return (printf("Parse Error\n"), 0);
// // 	else if (error == 2)
// // 		return (printf("Malloc failed\n"), ft_env(NULL, FREE, NULL, NULL), 2);
// // // 	free(input);
// // 	// }
// // 	ft_env(NULL, FREE, NULL, NULL);
// }
