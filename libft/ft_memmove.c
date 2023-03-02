/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:19:24 by tedelin           #+#    #+#             */
/*   Updated: 2022/11/15 11:04:58 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = -1;
	if (dest < src)
	{
		while (++i < n)
			*(char *)(dest + i) = *(char *)(src + i);
	}
	else
	{
		while ((int)(--n) >= 0)
			*(char *)(dest + n) = *(char *)(src + n);
	}
	return (dest);
}
