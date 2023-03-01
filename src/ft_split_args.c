/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:56:58 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/01 15:05:12 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	ft_status(char c)
{
	static int	status = 0;

	if (c == 39 && status == 0)
		status = 1;
	else if (c == '\"' && status == 0)
		status = 2;
	else if (status == 1 && c == 39)
		status = 0;
	else if (status == 2 && c == '\"')
		status = 0;
	return (status);
}

int	ft_len(char *s, int *j)
{
	int	len;
	int	state;
	int	tmp;

	while (s[*j] == ' ')
		(*j)++;
	state = 0;
	len = 0;
	while (s[len + *j])
	{
		tmp = state;
		state = ft_status(s[len + *j]);
		len++;
		if (state == 0 && tmp != 0)
			break ;
		if (s[len + *j] == ' ' && state == 0)
			break ;
	}
	return (len);
}

char	*ft_split(char *s)
{
	int			len;
	char		*res;
	int			i;
	static int	j = 0;

	while (s[j] == ' ')
			j++;
	if (!s || (s && s[j] == 0))
		return (NULL);
	len = ft_len(s, &j);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
		res[i++] = s[(j)++];
	res[i] = 0;
	return (res);
}

void	display(char *s)
{
	char	*res;

	res = ft_split(s);
	while (res != NULL)
	{
		printf("%s\n", res);
		res = ft_split(s);
	}
}

int	main(void)
{
	display("      < in awk      ''   \"      f     \" \"'{print $2}'\"   ");
}
