/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:52:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/06 12:07:29 by tedelin          ###   ########.fr       */
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
		while (s[++len + j] && ft_status(s[len + j], 0) == state)
			;
		str = ft_substr(s, j, len);
		j += len + 1;
		if ((state == 0 || state == 2) && ft_strchr(str, '$'))
			str = ft_dollar(str, state);
		if (state != 0)
			magic_space(str, 0);
		final = ft_strjoin(final, str, 3);
	}
	ft_expand(new, final, type);
}

int	ft_lim_len(char *s)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s && s[++i])
	{
		ft_status(s[i], 0);
		j++;
		if ((s[i] == '$' && ft_status(0, 2) == 0) || s[i] == 34 || s[i] == 39)
			j--;
	}
	return (j);
}

void	ft_lim(t_token **new, char *s, int type)
{
	char	*new_s;
	int		i;
	int		j;

	new_s = malloc(sizeof(char) * (ft_lim_len(s) + 1));
	if (!new_s)
		return ;
	i = -1;
	j = 0;
	ft_status(0, 1);
	while (s && s[++i])
	{
		ft_status(s[i], 0);
		if ((s[i] == '$' && ft_status(0, 2) > 0) || (s[i] != 34 && s[i] != 39
				&& s[i] != '$'))
			new_s[j++] = s[i];
	}
	new_s[j] = 0;
	t_lstadd_back(new, t_lstnew(new_s, type));
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
		if (cur->type == WORD || cur->type == FD)
			new_token(&new, cur->value, cur->type);
		else if (cur->type == LIM)
			ft_lim(&new, cur->value, cur->type);
		else
			t_lstadd_back(&new, t_lstnew(ft_strdup(cur->value), cur->type));
		cur = cur->next;
	}
	return (free_lst(lst), build_cmd(&new));
}
