/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:10:45 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/02 21:43:56 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_type(t_token *token)
{
	if (token->value && (!ft_strncmp(token->value, ">>", 2)
        || !ft_strncmp(token->value, "<<", 2)
		|| !ft_strncmp(token->value, ">", 1)
		|| !ft_strncmp(token->value, "<", 1)))
	{
		if (!ft_strncmp(token->value, ">>", 2))
			token->type = HOUT;
		else if (!ft_strncmp(token->value, ">", 1))
			token->type = OUT;
		else if (!ft_strncmp(token->value, "<", 1))
			token->type = IN;
		if (!ft_strncmp(token->value, "<<", 2))
			token->type = HIN;
		if (token->type == HIN)
		{
			token = token->next;
			if (token)
				token->type = LIM;
		}
		else
		{
			token = token->next;
			if (token)
				token->type = FD;
		}
	}
}

void	ft_type(t_token **token)
{
	t_token	*cur;

	cur = *token;
	while (cur)
	{
		get_type(cur);
		if (cur->value && !ft_strncmp(cur->value, "|", 1))
			cur->type = PIPE;
		cur = cur->next;
	}
}

int	main(void)
{
	char *s;
	t_token *token;

	s = "' '";
	token = make_token(s);
	ft_type(&token);
	if (ft_parser(&token) == 1)
		printf("ERROR\n");
	else
		printf("SUCESS\n");
	while (token)
	{
		printf("token:%s, type:%d\n", token->value, token->type);
		token = token->next;
	}
}