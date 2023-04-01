/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:52:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/01 18:20:38 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	magic_space(char *s, int rm)
{
	int	i;

	i = -1;
	while (s && s[++i])
	{
		if ((s[i] == ' ' && rm == 0) || (s[i] == -32 && rm == 1))
			s[i] = s[i] * -1;
	}
}

void	ft_expand(t_token **new, char *s, int type)
{
	char	**args;
	int		i;

	if (s && !s[0])
	{
		t_lstadd_back(new, t_lstnew(ft_strdup(s), type));
		free(s);
		return ;
	}
	args = ft_split(s, ' ');
	i = -1;
	while (args && args[++i])
		magic_space(args[i], 1);
	i = -1;
	while (args && args[++i])
		t_lstadd_back(new, t_lstnew(ft_strdup(args[i]), type));
	tab_free(args);
	free(s);
}

void	new_token(t_token **new, char *s, int type)
{
	int		j;
	int		len;
	char	*str;
	char	*final;
	int		state;

	j = 0;
	final = NULL;
	while (s && j < (int)ft_strlen(s) && s[j])
	{
		state = ft_status(s[j], 0);
		len = -1;
		if ((state == 2 && s[j] == 34) || (state == 1 && s[j] == 39))
			j++;
		while (s[++len + j] && ft_status(s[len + j], 0) == state);
		str = ft_substr(s, j, len);
		j += len + 1;
		if ((state == 0 || state == 2) && ft_strchr(str, '$'))
			str = ft_dollar(str);
		if (state != 0)
			magic_space(str, 0);
		if (str)
			final = ft_strjoin(final, str, 3);
	}
	ft_expand(new, final, type);
}

int	ft_expansion(t_token **lst)
{
	t_token	*new;
	t_token	*cur;

	new = NULL;
	cur = *lst;
	while (cur && cur->value)
	{
		ft_status(0, 1);
		new_token(&new, cur->value, cur->type);
		cur = cur->next;
	}
	return (free_lst(lst), build_cmd(&new));
}
