/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:52:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/14 15:43:11 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	new_t_token(t_token *previous, char *value, int type)
// {
// 	t_token	new;

// 	new = t_lstnew(value, type);
// 	previous->next = new;
// 	new->next =
// }

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

char *ft_var(char *new_str)
{
	int	i;
	int	j;
	int	k;
	char *var;

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
			// printf("str:%s, j:%d, i:%d\n", &new_str[i], j, i);
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

// char	*ft_dollar(char *new_str)
// {
// 	char	*good_str;
// 	char	*var;
// 	int		i;
// 	int		j;

// 	good_str = malloc(sizeof(char) * (ft_strlen(new_str)
// 				- ft_var(new_str) + 1));
// 	i = 0;
// 	j = 0;
// 	while (new_str[i] != '$')
// 		good_str[j++] = new_str[i++];
// 	var = get_var()
// 	i += ft_dollar_len(new_str);
// 	while (new_str[i])
// 		good_str[j++] = new_str[i++];
// 	return (NULL);
// }

void	new_token(t_token *current, t_token *previous)
{
	int		i;
	int		len;
	char	*new_str;
	t_token	*next;

	next = current->next;
	while (*current->value)
	{
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
		// if ((ft_status(0, 2) == 0 || ft_status(0, 2) == 2) && ft_strchr(new_str,
		// 		'$'))
			// new_str = ft_dollar(new_str);
		if (new_str && new_str[0])
			printf("%s\n", new_str);
		// new_t_token(previous, new_str, current->type);
		free(new_str);
	}
}

int	ft_change(char *value)
{
	ft_status(0, 1);
	while (*value)
	{
		if (ft_status(*value, 0))
			return (1);
		value++;
	}
	return (0);
}

void	ft_expansion(t_token **lst)
{
	t_token *current;
	t_token *previous;

	current = *lst;
	previous = NULL;
	while (current)
	{
		if ((current->type == WORD || current->type == FD)
			&& ft_change(current->value))
			new_token(current, previous);
		previous = current;
		current = current->next;
	}
}