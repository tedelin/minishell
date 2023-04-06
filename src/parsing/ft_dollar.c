/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:20:40 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/06 22:16:10 by tedelin          ###   ########.fr       */
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
	while (s && s[*i] && s[*i] == '$')
		(*i)++;
	if (s && !s[*i] && (*i > 1 || (*i == 1 && state == 2)))
		return (*i);
	else if (s && !s[*i] && *i == 1 && state != 2)
		return (0);
	else
	{
		tmp = ft_var(&s[*i]);
		while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_' || s[*i] == '?'))
			(*i)++;
		ft_env(NULL, GET, tmp, &res);
		len += ft_strlen(res);
		free(tmp);
		free(res);
		return (len);
	}
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
		if (s[i] == '$')
			len += handle_len_dollar(s, &i, state);
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
	while (s[*j] && (ft_isalnum(s[*j]) || s[*j] == '_' || s[*j] == '?'))
		(*j)++;
	k = 0;
	while (res && res[k])
		new[++(*i)] = res[k++];
	free(tmp);
	free(res);
}

void	handle_expand(char *s, char *new, int *i, int *j, int state)
{
	int	tmp;

	tmp = 0;
	while (s[*j + tmp] && s[*j + tmp] == '$')
		tmp++;
	if (s && !s[*j + tmp] && (tmp > 1 || (tmp == 1 && state == 2)))
	{
		while (s[*j] && s[*j] == '$')
			new[++(*i)] = s[(*j)++];
	}
	else if (s && !s[*i + tmp] && tmp == 1 && state != 2)
	{
		(*j)++;
		return ;
	}
	else
	{
		(*j)++;
		ft_expand_var(s, new, i, j);
	}
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
			handle_expand(s, new, &i, &j, state);
	}
	new[++i] = 0;
	return (free(s), new);
}
