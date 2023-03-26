/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:09:48 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/26 17:52:21 by mcatal-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_token	*lst;

	(void)ac;
	(void)av;
	ft_env(env, INIT, NULL);
	while (1)
	{
		input = readline("minishell>");
		if (!input)
			return (1);
		lst = NULL;
		add_history(input);
		if (make_token(&lst, input))
		{
			printf("Parse Error\n");
			return (0);
		}
		free(input);
	}
	ft_env(NULL, FREE, NULL);
}
