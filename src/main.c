/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:09:48 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/16 15:03:41 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_token	*lst;

	lst = NULL;
	ft_get_env(env, 0);
	// input = readline("minishell$");
	input = "< in awk 'print $2'hello | ls > out";
	if (!input)
		return (1);
	if (make_token(&lst, input))
	{
		printf("Parse Error\n");
		return (0);
	}
	// free(input);
}
