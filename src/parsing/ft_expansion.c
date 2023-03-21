/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:52:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/21 14:20:31 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_token(t_token *current)
{
	int		i;
	int		len;
	char	*str;

	if (!current->value)
		return (NULL);
	ft_status(0, 1);
	i = -1;
	len = -1;
	if (*current->value == 39 || *current->value == 34)
		current->value++;
	while (!ft_status(current->value[++len], 0) && current->value[len])
		;
	str = malloc(sizeof(char) * (len + 1));
	while (++i < len)
		str[i] = *current->value++;
	str[i] = '\0';
	if ((ft_status(0, 2) == 0 || ft_status(0, 2) == 2) && ft_strchr(str, '$'))
		str = ft_dollar(str);
	if (str && str[0])
		return (str);
	return (free(str), NULL);
}

int	ft_expansion(t_token **lst)
{
	t_token	*new;
	t_token	*cur;
	char	*add;
	char	*tmp;
	char	*state;

	new = NULL;
	add = NULL;
	cur = *lst;
	while (cur)
	{
		state = cur->value;
		tmp = new_token(cur);
		while (tmp)
		{
			add = ft_strjoin(add, tmp, 3);
			tmp = new_token(cur);
		}
		t_lstadd_back(&new, t_lstnew(add, cur->type));
		add = NULL;
		cur->value = state;
		cur = cur->next;
	}
	return (free_lst(lst), build_cmd(&new));
}

// free_lst(&new);
// 	free_lst(lst);
// 	printf("------------------------\n------------------------\n");