/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:51:54 by tedelin           #+#    #+#             */
/*   Updated: 2022/11/14 13:13:24 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while ((char *)(s + i) && i < n)
	{
		if (*(unsigned char *)(s + i) == (unsigned char)(c))
			return ((void *)(s + i));
		i++;
	}
	return (0);
}
