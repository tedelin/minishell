/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:20:40 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/12 19:30:05 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_var(char *s)
{
	int		i;
	char	*var;

	if (s && s[0] == '?')
		return (ft_strdup("?"));
	i = 0;
	while (s && ft_isalnum(s[i]))
		i++;
	if (!s || s[i] == '_')
		return (NULL);
	var = ft_substr(s, 0, i);
	return (var);
}

int	handle_len_dollar(char *s, int *i, int state)
{
	int		len;
	char	*tmp;
	char	*res;

	len = 0;
	res = NULL;
	(void) state;
	if (s[*i] == '_')
		return (0);
	if (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '?'))
	{
		tmp = ft_var(&s[*i]);
		while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_' || s[*i] == '?'))
			(*i)++;
		ft_env(NULL, GET, tmp, &res);
		len += ft_strlen(res);
		free(tmp);
		free(res);
	}
	else
		len++;
	return (len);
}

int	len_d(char *s, int state)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s && s[i])
	{
		len += ft_len_until(&s[i], '$');
		i += ft_len_until(&s[i], '$');
		if (s[i] == '$' && !s[i + 1])
			len++;
		if (s[i] && s[i++] == '$' && s[i])
			len += handle_len_dollar(s, &i, state);
	}
	return (len);
}

void	ft_expand_var(char *s, char *new, int *i, int *j)
{
	int		k;
	char	*tmp;
	char	*res;

	*j += 1;
	res = NULL;
	tmp = ft_var(&s[*j]);
	ft_env(NULL, GET, tmp, &res);
	while (s[*j] && (ft_isalnum(s[*j]) || s[*j] == '_' || s[*j] == '?'))
		(*j)++;
	k = 0;
	while (res && res[k])
		new[++(*i)] = res[k++];
	free(tmp);
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
		if (s[j] == '$')
		{
			if (s[j + 1] && (ft_isalnum(s[j + 1])
					|| s[j + 1] == '_' || s[j + 1] == '?'))
				ft_expand_var(s, new, &i, &j);
			else
				new[++i] = s[j++];
		}
	}
	new[++i] = 0;
	return (free(s), new);
}
