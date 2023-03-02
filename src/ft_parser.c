/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:13:01 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/02 19:00:24 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pipe au debut ou a la fin
// quotes 
// redirections pas 3 a la suite
// pas de redirection opposer

// int	check_quotes(char *s)
// {
// 	int state;
//     int quote;
//     int dquotes;
//     int i;

//     i = 0;
//     quote = 0;
//     dquotes = 0;
// 	state = ft_status(s[0], 1);
// 	while(s[i])
//     {
//         if(state == 0 && s[i] == 34)
//             dquotes++;
//         else if (state == 0 && s[i] == 39)
//             quote++;
//         i++;
//         state = ft_status(s[i], 0);
//     }
//     if ((dquotes % 2 == 0 && quote % 2 == 0) && state == 0)
//         return (0);
//     return(1);
// }

int	check_quotes(char *s)
{
	int state;
	int i;

	i = 0;
	state = ft_status(s[i++], 1);
	while (s[i])
	{
		state = ft_status(s[i], 0);
		i++;
	}
	if (state == 0)
		return (0);
	return (1);
}

int	ft_parser(t_token **token)
{
	t_token *begin;

	begin = *token;
	if (begin->type == PIPE && check_quotes(begin->value))
		return (1);
	while (begin->next)
	{
		if (check_quotes(begin->value) == 1)
			return (1);
		if (begin->type >= IN && begin->type <= HOUT)
		{
			if (begin->next && begin->next->type != FD && begin->next->type != LIM)
				return (1);
		}
		begin = begin->next;  
	}
	if (begin->type >= IN && begin->type <= PIPE)
		return (1);
	return (0);
}
