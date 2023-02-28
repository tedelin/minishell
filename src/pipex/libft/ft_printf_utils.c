/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 03:11:33 by tedelin           #+#    #+#             */
/*   Updated: 2022/12/13 15:36:38 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

size_t	ft_puthexamaj(unsigned int nb)
{
	if (nb / 16)
		return (ft_puthexamaj(nb / 16) + ft_puthexamaj(nb % 16));
	if (nb >= 10 && nb < 16)
		ft_putchar((nb % 10) + 'A');
	if (nb < 10)
		ft_putchar((nb % 10) + '0');
	return (1);
}

size_t	ft_puthexamin(unsigned int nb)
{
	if (nb / 16)
		return (ft_puthexamin(nb / 16) + ft_puthexamin(nb % 16));
	if (nb >= 10 && nb < 16)
		ft_putchar((nb % 10) + 'a');
	if (nb < 10)
		ft_putchar((nb % 10) + '0');
	return (1);
}

int	ft_putunsnbr(unsigned int nb)
{
	if (nb >= 10)
		return (ft_putunsnbr(nb / 10) + ft_putunsnbr(nb % 10));
	else
		return (ft_putchar(nb + '0'));
}

int	ft_putnbr(int n)
{
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	else if (n < 0)
		return (ft_putchar('-') + ft_putnbr(-n));
	else if (n >= 0 && n <= 9)
		return (ft_putchar(n + 48));
	else
		return (ft_putnbr(n / 10) + ft_putnbr(n % 10));
}
