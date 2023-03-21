/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:09:48 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/21 10:03:16 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_token	*lst;

	ft_env(env, INIT, NULL);
	input = readline("minishell$");
	// input = "echo > a > b > c test";
	if (!input)
		return (1);
	// if (!ft_strncmp("exit", input, 4))
	// 	exit(0);
	lst = NULL;
	ft_env(NULL, ADD, "T=\"test\"");
	if (make_token(&lst, input))
	{
		printf("Parse Error\n");
		return (0);
	}
	free(input);
	ft_env(NULL, FREE, NULL);
}
