/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:13:01 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/27 11:24:17 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_next_type(char *next)
{
	if (!next)
		return (0);
	else if (!ft_strncmp(next, "|", 1))
		return (PIPE);
	else if (!ft_strncmp(next, "<<", 2))
		return (DRIN);
	else if (!ft_strncmp(next, ">>", 2))
		return (DROUT);
	else if (!ft_strncmp(next, ">", 1))
		return (ROUT);
	else if (!ft_strncmp(next, "<", 1))
		return (RIN);
	return (0);
}

int	ft_type(t_token **token)
{
	t_token	*cur;

	cur = *token;
	while (cur)
	{
		if (cur->value && !ft_strncmp(cur->value, "|", 1))
			cur->type = PIPE;
		else if (cur->value && !ft_strncmp(cur->value, "<<", 2))
			cur->type = DRIN;
		else if (cur->value && !ft_strncmp(cur->value, ">>", 2))
			cur->type = DROUT;
		else if (cur->value && !ft_strncmp(cur->value, ">", 1))
			cur->type = ROUT;
		else if (cur->value && !ft_strncmp(cur->value, "<", 1))
			cur->type = RIN;
		if (cur->type == DRIN && cur->next && !ft_next_type(cur->next->value))
			cur->next->type = LIM;
		else if (cur->next && cur->type != WORD && cur->type != PIPE
			&& !ft_next_type(cur->next->value))
			cur->next->type = FD;
		if (cur->next && cur->next->type != WORD)
			cur = cur->next;
		cur = cur->next;
	}
	return (ft_parser(token));
}

int	check_quotes(char *s)
{
	int	i;
	int	count;
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
	while (s[i] && s[i + 1] && s[i] != s[old_i])
		i++;
	if (old_i != i && s[i] == s[old_i])
		count++;
	if ((count != 2 && count != 0) || (count == 1 && ft_strlen(s) == 1))
		return (1);
	return (0);
}

int	ft_parser(t_token **token)
{
	t_token	*begin;

	begin = *token;
	if (begin && begin->type == PIPE)
		return (1);
	while (begin && begin->next)
	{
		if (check_quotes(begin->value))
			return (1);
		if (begin->type >= RIN && begin->type <= DROUT)
		{
			if (begin->next && begin->next->type != FD
				&& begin->next->type != LIM)
				return (1);
		}
		begin = begin->next;
	}
	if (check_quotes(begin->value) || (begin->type >= RIN
			&& begin->type <= PIPE))
		return (1);
	return (ft_expansion(token));
}
