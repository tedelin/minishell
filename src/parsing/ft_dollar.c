/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:20:40 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/29 15:50:37 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_var(char *s)
{
	int		i;
	int		j;
	char	*var;

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

int	len_d(char *s)
{
	int		i;
	int		len;
	char	*tmp;
	char *res;

	res = NULL;
	i = 0;
	len = 0;
	while (s && s[i])
	{
		while (s[i] && s[i] != '$')
		{
			i++;
			len++;
		}
		if (s[i] && s[i++] == '$')
		{
			tmp = ft_var(&s[i]);
			while (s[i] && (ft_isalnum(s[i]) || s[i] == '_'))
				i++;
			ft_env(NULL, GET, tmp, res);
			len += ft_strlen(res);
			free(tmp);
		}
	}
	return (len);
}

void	ft_expand_var(char *s, char *new, int *i, int *j)
{
	char	*tmp;
	char	*res;

	res = NULL;
	tmp = ft_var(&s[*j]);
	ft_env(NULL, GET, tmp, res);
	free(tmp);
	while (s[*j] && (ft_isalnum(s[*j]) || s[*j] == '_'))
		(*j)++;
	while (res && *res)
		new[++(*i)] = *res++;
}

char	*ft_dollar(char *s)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = 0;
	new = malloc(sizeof(char) * (len_d(s) + 1));
	if (!new)
		return (free(s), NULL);
	while (s && s[j])
	{
		while (s[j] && s[j] != '$')
			new[++i] = s[j++];
		if (s[j] && s[j++] == '$')
			ft_expand_var(s, new, &i, &j);
	}
	new[++i] = 0;
	return (free(s), new);
}
