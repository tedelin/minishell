/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 01:26:39 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/12 14:43:29 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

int	ft_checknext(char c)
{
	int		i;
	char	*ref;

	ref = "cspdiuxX%";
	i = 0;
	if (c != '\0')
	{
		while (ref[i])
		{
			if (ref[i] == c)
				return (1);
			i++;
		}
	}
	return (0);
}

int	ft_display(int fd, va_list va_l, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count = ft_putchar(fd, va_arg(va_l, int));
	if (c == 's')
		count = ft_putstr(fd, va_arg(va_l, char *));
	if (c == 'p')
		count = ft_adresse(fd, va_arg(va_l, unsigned long));
	if (c == 'i' || c == 'd')
		count = ft_putnbr(fd, va_arg(va_l, int));
	if (c == 'u')
		count = ft_putunsnbr(fd, va_arg(va_l, unsigned int));
	if (c == 'x')
		count = ft_puthexamin(fd, va_arg(va_l, unsigned int));
	if (c == 'X')
		count = ft_puthexamaj(fd, va_arg(va_l, unsigned int));
	if (c == '%')
		count = ft_putchar(fd, '%');
	return (count);
}

int	ft_fprintf(int fd, const char *s, ...)
{
	va_list	va_l;
	int		len;
	int		i;

	va_start(va_l, s);
	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] == '%' && ft_checknext(s[i + 1]))
			len += ft_display(fd, va_l, s[++i]);
		else
			len += ft_putchar(fd, s[i]);
		i++;
	}
	va_end(va_l);
	return (len);
}
