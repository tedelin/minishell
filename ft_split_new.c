/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 13:43:58 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/01 10:52:110 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int		ft_status(char c)
{
    static int status = 0;

	if (c == '\'' && status == 0)
		status = 1;
	else if (c == 34 && status == 0)
		status = 2;
	else if (status == 1 && c == '\'')
		status = 0;
	else if (status == 2 && c == 34)
		status = 0;
	return (status);
}

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '>' || c == '<')
		return (1);
	return (0);
}

int	is_last(char *s, int i)
{
	while (s[i])
	{
		if (ft_isalpha(s[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	ft_count(char *s)
{
	int i;
	int count;
	int	temp;

	i = 0;
	count = 0;
	while (s && s[i])
	{
		temp = ft_status(s[i]);
		if (ft_isalpha(s[i]) == 1)
		{
			count++;
			while (ft_isalpha(s[i]) == 1)
				i++;
		}
		else if (temp == 2)
		{
			count++;
			i++;
			while (ft_status(s[i]) == temp)
				i++;
			i++;
		}
		else if (temp == 1)
		{
			count++;
			i++;
			while (ft_status(s[i]) == temp)
				i++;
			i++;
		}
		else
			i++;
	}
	if (s && is_last(s, i) == 1)
		count++;
	return (count);
}


int main(int ac, char **av)  
{
    printf("%d", ft_count("< < \"Makefile  test\"  awk '{print $2}' | cat > /dev/stdout"));
}