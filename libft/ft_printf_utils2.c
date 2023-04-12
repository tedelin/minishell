/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:26:25 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/12 14:45:44 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(int fd, char *str)
{
	if (!str)
		return (write(fd, "(null)", 6));
	return (write(fd, str, ft_strlen(str)));
}

int	ft_l_adresse(unsigned long p)
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

int	ft_adresse(int fd, unsigned long p)
{
	int		i;
	char	*res;
	char	*base;
	int		len;

	if (!p)
		return (write(fd, "(nil)", 5));
	i = ft_l_adresse(p);
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
	len = ft_putstr(fd, "0x") + ft_putstr(fd, res);
	free(res);
	return (len);
}
