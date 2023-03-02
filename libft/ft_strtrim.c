/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:30:33 by tedelin           #+#    #+#             */
/*   Updated: 2022/11/17 17:48:12 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(char const *set, char c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		start;
	int		end;
	int		j;

	start = 0;
	end = ft_strlen(s1);
	while (end - 1 > 0 && ft_check(set, s1[end - 1]))
		end--;
	while (s1[start] && ft_check(set, s1[start]))
		start++;
	if ((end - start) >= 0)
		new = (char *)malloc(sizeof(char) * ((end - start) + 1));
	else
		new = malloc(sizeof(char));
	if (new)
	{
		j = 0;
		while (s1[start] && start < end)
			new[j++] = s1[start++];
		new[j] = 0;
	}
	return (new);
}
