/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:52:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/26 18:15:47 by mcatal-d         ###   ########.fr       */
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

void	ft_expand(t_token **new, char *s)
{
	char	**args;
	int		i;

	args = ft_split(s, ' ');
	i = -1;
	while (args && args[++i])
		magic_space(args[i], 1);
	i = -1;
	while (args && args[++i])
		t_lstadd_back(new, t_lstnew(args[i], WORD));
}

void	new_token(char *s, t_token **new, int j, char *final)
{
	int		i;
	int		len;
	int		state;
	char	*str;

	while (s && s[j])
	{
		ft_status(0, 1);
		i = -1;
		len = -1;
		state = ft_status(s[j], 0);
		if (s[j] == 39 || s[j] == 34)
			j++;
		while (ft_status(s[++len + j], 0) == state && s[len + j])
			;
		str = ft_substr(s, j, len);
		j += len;
		if ((state == 0 || state == 2) && ft_strchr(str, '$'))
			str = ft_dollar(str, state, 0);
		if (state == 2)
			magic_space(str, 0);
		final = ft_strjoin(final, str, 0);
	}
	ft_expand(new, final);
}

int	ft_expansion(t_token **lst)
{
	t_token	*new;
	t_token	*cur;
	char	*state;

	new = NULL;
	cur = *lst;
	while (cur && cur->value)
	{
		new_token(cur->value, &new, 0, NULL);
		cur = cur->next;
	}
	return (free_lst(lst), build_cmd(&new));
}
// print_lst(&new);
// return (0);
