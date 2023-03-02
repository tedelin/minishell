/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 19:21:32 by tedelin           #+#    #+#             */
/*   Updated: 2022/11/18 19:21:35 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	l_dst;
	size_t	l_src;

	l_dst = ft_strlen(dst);
	l_src = ft_strlen(src);
	i = l_dst;
	if (size <= l_dst)
		return (size + l_src);
	j = 0;
	while (src[j] && i < size - 1)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (l_dst + l_src);
}
