/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 03:11:33 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/12 14:44:08 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putchar(int fd, char c)
{
	return (write(fd, &c, 1));
}

size_t	ft_puthexamaj(int fd, unsigned int nb)
{
	if (nb / 16)
		return (ft_puthexamaj(fd, nb / 16) + ft_puthexamaj(fd, nb % 16));
	if (nb >= 10 && nb < 16)
		ft_putchar(fd, (nb % 10) + 'A');
	if (nb < 10)
		ft_putchar(fd, (nb % 10) + '0');
	return (1);
}

size_t	ft_puthexamin(int fd, unsigned int nb)
{
	if (nb / 16)
		return (ft_puthexamin(fd, nb / 16) + ft_puthexamin(fd, nb % 16));
	if (nb >= 10 && nb < 16)
		ft_putchar(fd, (nb % 10) + 'a');
	if (nb < 10)
		ft_putchar(fd, (nb % 10) + '0');
	return (1);
}

int	ft_putunsnbr(int fd, unsigned int nb)
{
	if (nb >= 10)
		return (ft_putunsnbr(fd, nb / 10) + ft_putunsnbr(fd, nb % 10));
	else
		return (ft_putchar(fd, nb + '0'));
}

int	ft_putnbr(int fd, int n)
{
	if (n == -2147483648)
		return (write(fd, "-2147483648", 11));
	else if (n < 0)
		return (ft_putchar(fd, '-') + ft_putnbr(fd, -n));
	else if (n >= 0 && n <= 9)
		return (ft_putchar(fd, n + 48));
	else
		return (ft_putnbr(fd, n / 10) + ft_putnbr(fd, n % 10));
}
