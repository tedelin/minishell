/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:20:40 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/06 12:09:40 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_var(char *s)
{
	int		i;
	int		j;
	char	*var;

	if (s && s[0] == '?')
		return (ft_strdup("?"));
	i = -1;
	while (s && ft_isalnum(s[++i]))
		;
	if (!s || s[i] == '_')
		return (NULL);
	var = malloc(sizeof(char) * (i + 1));
	j = -1;
	while (s && ++j < i)
		var[j] = s[j];
	var[j] = 0;
	return (var);
}

int	len_d(char *s, int state)
{
	int		i;
	int		len;
	char	*tmp;
	char	*res;

	res = NULL;
	i = 0;
	len = 0;
	while (s && s[i])
	{
		while (s[i] && s[i] != '$' && ++len)
			i++;
		if (s[i] && s[i++] == '$')
		{
			if (!s[i] && state == 2)
				len++;
			else
			{
				tmp = ft_var(&s[i]);
				while (s[i] && (ft_isalnum(s[i]) || s[i] == '_' || s[i] == '?'))
					i++;
				ft_env(NULL, GET, tmp, &res);
				free(tmp);
				len += ft_strlen(res);
				free(res);
			}
		}
	}
	return (len);
}

void	ft_expand_var(char *s, char *new, int *i, int *j)
{
	int		k;
	char	*tmp;
	char	*res;

	res = NULL;
	tmp = ft_var(&s[*j]);
	ft_env(NULL, GET, tmp, &res);
	free(tmp);
	while (s[*j] && (ft_isalnum(s[*j]) || s[*j] == '_' || s[*j] == '?'))
		(*j)++;
	k = 0;
	while (res && res[k])
		new[++(*i)] = res[k++];
	free(res);
}

char	*ft_dollar(char *s, int state)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = 0;
	new = malloc(sizeof(char) * (len_d(s, state) + 1));
	if (!new)
		return (free(s), NULL);
	while (s && s[j])
	{
		while (s[j] && s[j] != '$')
			new[++i] = s[j++];
		if (s[j] && s[j] == '$')
		{
			if (s[j] == '$' && !s[j + 1] && state == 2)
				new[++i] = s[j++];
			else
			{
				j++;
				ft_expand_var(s, new, &i, &j);	
			}
		}
	}
	new[++i] = 0;
	return (free(s), new);
}
