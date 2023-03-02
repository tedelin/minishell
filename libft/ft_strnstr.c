/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:50:37 by tedelin           #+#    #+#             */
/*   Updated: 2022/11/17 14:43:54 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	l_little;

	l_little = ft_strlen(little);
	if (l_little == 0)
		return ((char *)(big));
	if (len == 0)
		return (0);
	i = 0;
	while (big[i] && i <= (len - l_little))
	{
		if (big[i] == little[0] && ft_strncmp(&big[i], little, l_little) == 0)
			return ((char *)(big + i));
		i++;
	}
	return (0);
}
