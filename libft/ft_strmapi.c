/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 14:17:32 by tedelin           #+#    #+#             */
/*   Updated: 2022/11/11 10:04:45 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	int		i;

	i = 0;
	while (s[i])
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (res)
	{
		i = 0;
		while (s[i])
		{
			res[i] = f(i, s[i]);
			i++;
		}
		res[i] = 0;
	}
	return (res);
}
