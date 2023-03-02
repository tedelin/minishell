/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:26:25 by tedelin           #+#    #+#             */
/*   Updated: 2022/12/13 15:36:54 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (write(1, "(null)", 6));
	while (str && str[i])
		ft_putchar(str[i++]);
	return (i);
}

int	ft_len(unsigned long p)
{
	int	len;

	len = 1;
	while (p >= 16)
	{
		p = p / 16;
		len++;
	}
	return (len);
}

int	ft_adresse(unsigned long p)
{
	int		i;
	char	*res;
	char	*base;
	int		len;

	if (!p)
		return (write(1, "(nil)", 5));
	i = ft_len(p);
	base = "0123456789abcdef";
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (0);
	res[i--] = '\0';
	while (p >= 16)
	{
		res[i--] = base[p % 16];
		p = p / 16;
	}
	res[i] = base[p % 16];
	len = ft_putstr("0x") + ft_putstr(res);
	free(res);
	return (len);
}
