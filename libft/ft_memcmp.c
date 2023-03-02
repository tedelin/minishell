/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:18:11 by tedelin           #+#    #+#             */
/*   Updated: 2022/11/14 17:16:20 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n )
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && *(char *)(s1 + i) == *(char *)(s2 + i) && (s1 + i)
			&& (s2 + i))
		i++;
	return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
}
