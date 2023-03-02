/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:19:16 by tedelin           #+#    #+#             */
/*   Updated: 2022/11/15 21:07:43 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static	int	ft_nblen(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n >= 10 || n <= -10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*res;
	int				i;
	unsigned int	nb;

	i = ft_nblen(n);
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	res[i--] = '\0';
	if (n < 0)
	{
		res[0] = '-';
		nb = -n;
	}
	else
		nb = n;
	while (nb >= 10)
	{
		res[i--] = (nb % 10) + '0';
		nb = nb / 10;
	}
	res[i] = (nb % 10) + '0';
	return (res);
}
