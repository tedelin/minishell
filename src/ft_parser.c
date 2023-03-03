/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:13:01 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/03 11:12:25 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quotes(char *s)
{
	int	i;
	int count;
	int	old_i;
	
	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (s[i] && s[i] != 34 && s[i] != 39)
		i++;
	old_i = i;
	if (s[i] == 34 || s[i] == 39)
	{
		count++;
		i++;
	}
	while (s[i + 1])
		i++;
	if (old_i != i && s[i] == s[old_i])
		count++;
	if ((count != 2 && count != 0) || (count == 1 && ft_strlen(s) == 1))
		return (1);
	return (0);
}

int	ft_parser(t_token **token)
{
	t_token *begin;

	begin = *token;
	if (begin->type == PIPE)
		return (1);
	while (begin->next)
	{
		if (check_quotes(begin->value))
			return (1);
		if (begin->type >= IN && begin->type <= HOUT)
		{
			if (begin->next && begin->next->type != FD && begin->next->type != LIM)
				return (1);
		}
		begin = begin->next;  
	}
	if (check_quotes(begin->value) || (begin->type >= IN && begin->type <= PIPE))
		return (1);
	return (0);
}
