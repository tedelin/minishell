/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:52:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/15 18:17:30 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(char **env, char *var)
{
	int	i;

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
	while (!ft_status(current->value[++len], 0) && current->value[len])
		;
	if (len == 0)
		return (NULL);
	new_str = malloc(sizeof(char) * (len + 1));
	i = -1;
	while (++i < len)
		new_str[i] = *current->value++;
	new_str[i] = '\0';
	// if ((ft_status(0, 2) == 0 || ft_status(0, 2) == 2) && ft_strchr(new_str,
	// 		'$'))
	// 	new_str = ft_dollar(new_str);
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
	free_lst(old);
	free_lst(new);
	return (0);
}
