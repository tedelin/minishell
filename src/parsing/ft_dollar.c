/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:20:40 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/26 23:08:50 by tedelin          ###   ########.fr       */
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
			len += ft_strlen(ft_env(NULL, GET, tmp));
			free(tmp);
		}
	}
	return (len);
}

char	*ft_dollar(char *s, int state)
{
	int		i;
	int		j;
	char	*new;
	char	*var;
	char	*tmp;

	i = -1;
	j = 0;
	new = malloc(sizeof(char) * (len_d(s) + 1));
	while (s && s[j])
	{
		while (s[j] && s[j] != '$')
			new[++i] = s[j++];
		if (s[j] && s[j++] == '$')
		{
			tmp = ft_var(&s[j]);
			var = ft_env(NULL, GET, tmp);
			free(tmp);
			while (s[j] && (ft_isalnum(s[j]) || s[j] == '_'))
				j++;
			while (var && *var)
				new[++i] = *var++;
		}
	}
	new[++i] = 0;
	return (free(s), new);
}
