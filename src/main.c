/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:09:48 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/15 18:11:48 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av)
{
	char	*input;
	t_token	*lst;

	lst = NULL;
	input = readline("minishell$");
	if (!input)
		return (1);
	if (make_token(&lst, input))
	{
		printf("Parse Error\n");
		return (0);
	}
	free(input);
}
