/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dollar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 10:20:40 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/17 17:40:08 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_var(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*var;

	j = 0;
	i = -1;
	k = 0;
	while (str && str[++i])
	{
		if (str[i] == '$')
		{
			j++;
			while (str[i + j] && ft_isalnum(str[i + j]))
				j++;
			if (str[i + j] == '_')
				return (NULL);
			var = malloc(sizeof(char) * j);
			while (k < j - 1)
				var[k++] = str[++i];
			var[i] = 0;
			return (var);
		}
	}
	return (NULL);
}

int	len_d(char *s)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = 0;
	while (s && s[i] && ft_strchr(&s[i], '$'))
	{
		while (s[i] && s[i] != '$')
		{
			len++;
			i++;
		}
		tmp = ft_var(&s[i]);
		len += ft_strlen(ft_env(NULL, GET, tmp));
		free(tmp);
		i++;
	}
	while (s && s[i] && len++)
		i++;
	return (len);
}

char	*ft_dollar(char *s)
{
	int		i;
	int		j;
	char	*new;
	char	*var;
	char	*tmp;

	i = -1;
	j = 0;
	new = malloc(sizeof(char) * (len_d(s) + 1));
	while (s && s[j] && ft_strchr(s, '$'))
	{
		tmp = ft_var(ft_strchr(&s[j], '$'));
		var = ft_env(NULL, GET, tmp);
		free(tmp);
		if (s[j] == '$')
			j++;
		while (s[j] && (ft_isalnum(s[j]) || s[j] == '_'))
			j++;
		while (var && *var)
			new[++i] = *var++;
		while (s[j] && s[j] != '$')
			new[++i] = s[j++];
	}
	new[++i] = 0;
	return (free(s), new);
}
