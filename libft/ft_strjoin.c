/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:14:19 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/11 15:04:25 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2, int opt)
{
	char	*new;
	int		j;
	int		i;

	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new)
	{
		j = 0;
		i = 0;
		while (s1 && s1[i])
			new[j++] = s1[i++];
		i = 0;
		while (s2 && s2[i])
			new[j++] = s2[i++];
		new[j] = '\0';
	}
	if (opt == 1 || opt == 3)
		free(s1);
	if (opt == 2 || opt == 3)
		free(s2);
	return (new);
}
