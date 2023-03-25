/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:52:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/25 10:56:37 by mcatal-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mult_token(char *str, t_token **new, char *final, int i)
{
	char	*join;
	char	*dollar;
	char	*first_part;
	int		j;

	j = 0;
	dollar = ft_dollar(str, 1, -1);
	while (dollar[i] && dollar[i] != ' ')
		i++;
	first_part = ft_substr(dollar, 0, i);
	join = ft_strjoin(final, first_part, 3);
	t_lstadd_back(new, t_lstnew(join, WORD));
	while (dollar[i] == ' ')
		i++;
	while (dollar && dollar[i])
	{
		j = i;
		while (dollar[i] && dollar[i] != ' ')
			i++;
		join = ft_substr(dollar, j, i - j);
		if (join && join[0])
			t_lstadd_back(new, t_lstnew(join, WORD));
		i++;
	}
}

void	new_token(char *s, t_token **new, int j)
{
	int		i;
	int		len;
	int		state;
	char	*str;
	char	*final;

	final = NULL;
	ft_status(0, 1);
	while (s && s[j])
	{
		i = -1;
		len = -1;
		state = ft_status(s[j], 0);
		if (s[j] == 39 || s[j] == 34)
			j++;
		if (!s[j])
			break ;
		while (ft_status(s[++len + j], 0) == state && s[len + j])
			str = malloc(sizeof(char) * (len + 1));
		while (++i < len)
			str[i] = s[j++];
		str[i] = '\0';
		if ((state == 2) && ft_strchr(str, '$'))
			str = ft_dollar(str, 0, -1);
		else if (state == 0 && ft_strchr(str, '$'))
		{
			mult_token(str, new, final, 0);
			str = NULL;
			final = NULL;
		}
		if (str && str[0])
			final = ft_strjoin(final, str, 0);
	}
	if (final)
		t_lstadd_back(new, t_lstnew(final, WORD));
	free(str);
}

int	ft_expansion(t_token **lst)
{
	t_token	*new;
	t_token	*cur;
	char	*add;
	char	*tmp;
	char	*state;

	new = NULL;
	add = NULL;
	cur = *lst;
	while (cur && cur->value)
	{
		new_token(cur->value, &new, 0);
		cur = cur->next;
	}
	print_lst(&new);
	return (free_lst(lst), build_cmd(&new));
}
