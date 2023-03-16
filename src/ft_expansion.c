/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:52:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/16 18:31:26 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char **env, char *var)
{
	int	i;

	i = -1;
	if (!var)
		return (NULL);
	while (env && env[++i])
	{
		if (!ft_strncmp(env[i], var, ft_strlen(var)))
			return (env[i] + ft_strlen(var) + 1);
	}
	return (NULL);
}

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
			i++;
			while (k < j - 1)
				var[k++] = str[i++];
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
	int		i;
	int		j;
	char	*new;
	char	*var;
	char	*tmp;

	new = malloc(sizeof(char) * (len_d(env, s) + 1));
	i = -1;
	j = 0;
	while (s && s[j] && ft_strchr(s, '$'))
	{
		tmp = ft_var(ft_strchr(&s[j], '$'));
		var = get_var(env, tmp);
		free(tmp);
		while (s[j] && s[j] != '$')
			new[++i] = s[j++];
		while (s[j] && ((ft_isalnum(s[j]) || s[j] == '$') || s[j] == '_'))
			j++;
		while (var && *var)
			new[++i] = *var++;
		while (s[j] && s[j] != '$')
			new[++i] = s[j++];
	}
	new[++i] = 0;
	return (free(s), new);
}

t_token	*new_token(t_token *current)
{
	t_token	*new;
	int		i;
	int		len;
	char	*str;

	ft_status(0, 1);
	i = -1;
	len = -1;
	if (*current->value == 39 || *current->value == 34)
		current->value++;
	while (!ft_status(current->value[++len], 0) && current->value[len]);
	str = malloc(sizeof(char) * (len + 1));
	while (++i < len)
		str[i] = *current->value++;
	str[i] = '\0';
	if ((ft_status(0, 2) == 0 || ft_status(0, 2) == 2) && ft_strchr(str, '$'))
		str = ft_dollar(ft_get_env(NULL, 1), str);
	if (str && str[0])
	{
		new = t_lstnew(str, current->type);
		return (new);
	}
	return (free(str), NULL);
}

int	ft_expansion(t_token **lst)
{
	t_token	*new;
	t_token	*add;
	t_token	*cur;
	char	*state;

	new = NULL;
	add = NULL;
	cur = *lst;
	while (cur)
	{
		state = cur->value;
		add = new_token(cur);
		while (add)
		{
			if (add)
				t_lstadd_back(&new, add);
			add = new_token(cur);
		}
		cur->value = state;
		cur = cur->next;
	}
	print_lst(&new);
	free_lst(lst);
	free_lst(&new);
	return (0);
}
