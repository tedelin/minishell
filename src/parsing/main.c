/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:09:48 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/17 18:17:26 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_token	*lst;

	ft_env(env, INIT, NULL);
	input = readline("minishell$");
	// input = "$PATH";
	if (!input)
		return (1);
	lst = NULL;
	if (make_token(&lst, input))
	{
		printf("Parse Error\n");
		return (0);
	}
	ft_export("TEST=t");
	// ft_export("TEST_=t");
	ft_export("TEST=tejflasf");
	ft_env(NULL, 10, NULL);
	free(input);
	ft_env(NULL, FREE, NULL);
}
