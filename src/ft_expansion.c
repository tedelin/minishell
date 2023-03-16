/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:52:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/16 15:32:43 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char **env, char *var)
{
	int	i;

	if (!var)
		return (NULL);
	i = -1;
	while (env && env[++i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
			return (env[i] + ft_strlen(var) + 1);
	}
	return (NULL);
}

char	*ft_var(char *new_str)
{
	int		i;
	int		j;
	int		k;
	char	*var;

	j = 0;
	i = -1;
	k = 0;
	while (new_str[++i])
	{
		if (new_str[i] == '$')
		{
			j++;
			while (new_str[i + j] && ft_isalnum(new_str[i + j]))
				j++;
			if (new_str[i + j] == '_')
				return (NULL);
			var = malloc(sizeof(char) * j);
			i++;
			while (k < j - 1)
				var[k++] = new_str[i++];
			var[i] = 0;
			return (var);
		}
	}
	return (NULL);
}

int	len_d(char **env, char *s)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s && s[i] && ft_strchr(&s[i], '$'))
	{
		while (s[i] && s[i] != '$')
		{
			len++;
			i++;
		}
		len += ft_strlen(get_var(env, ft_var(&s[i])));
		i++;
	}
	while (s && s[i] && len++)
		i++;
	return (len);
}

char	*ft_dollar(char **env, char *s)
{
	char	*new;
	int	i;
	char *var;

	new = malloc(sizeof(char) * (len_d(env, s) + 1));
	i = -1;
	while (*s && ft_strchr(s, '$'))
	{
		var = get_var(env, ft_var(ft_strchr(s, '$')));
		while (*s && *s != '$')
			new[++i] = *s++;
		while (*s && ((ft_isalnum(*s) || *s == '$') || *s == '_'))
			s++;
		while (var && *var)
			new[++i] = *var++;
		while (*s && *s != '$')
			new[++i] = *s++;
	}
	new[++i] = 0;
	return (new);
}

t_token	*new_token(t_token *current)
{
	t_token	*new;
	int		i;
	int		len;
	char	*new_str;

	ft_status(0, 1);
	if (*current->value == 39 || *current->value == 34)
		current->value++;
	len = -1;
	while (!ft_status(current->value[++len], 0) && current->value[len]);
	new_str = malloc(sizeof(char) * (len + 1));
	i = -1;
	while (++i < len)
		new_str[i] = *current->value++;
	new_str[i] = '\0';
	if ((ft_status(0, 2) == 0 || ft_status(0, 2) == 2) && ft_strchr(new_str,
			'$'))
		new_str = ft_dollar(ft_get_env(NULL, 1), new_str);
	if (new_str && new_str[0])
	{
		new = t_lstnew(new_str, current->type);
		return (new);
	}
	return (free(new_str), NULL);
}

int	ft_expansion(t_token **lst)
{
	t_token	*new;
	t_token	*add;
	t_token	*old;

	new = NULL;
	old = *lst;
	add = NULL;
	while ((*lst))
	{
		add = new_token(*lst);
		while (add)
		{
			if (add)
				t_lstadd_back(&new, add);
			add = new_token(*lst);
		}
		(*lst) = (*lst)->next;
	}
	print_lst(&new);
	free_lst(&old);
	free_lst(&new);
	return (0);
}
