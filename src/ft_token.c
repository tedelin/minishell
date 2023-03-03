/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:10:45 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/03 11:45:34 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_type(t_token **token)
{
	t_token	*cur;

	cur = *token;
	while (cur)
	{
		if (cur->value && !ft_strncmp(cur->value, "|", 1))
			cur->type = PIPE;
		if (cur->value && !ft_strncmp(cur->value, ">>", 2))
			cur->type = HOUT;
		else if (cur->value && !ft_strncmp(cur->value, ">", 1))
			cur->type = OUT;
		else if (cur->value && !ft_strncmp(cur->value, "<", 1))
			cur->type = IN;
		else if (cur->value && !ft_strncmp(cur->value, "<<", 2))
			cur->type = HIN;
		if (cur->type == HIN && cur->next)
			cur->next->type = LIM;
		else if (cur->next && cur->type != WORD)
			cur->next->type = FD;
		if (cur->next && cur->next->type != WORD)
			cur = cur->next;
		cur = cur->next;
	}
}

int	main(void)
{
	char *s;
	t_token *token;

	s = NULL;
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