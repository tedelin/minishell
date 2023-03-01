/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tedelin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:24:43 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/01 10:55:55 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	check(char c, char *charset)
{
	int i;

	i = 0;
	while (charset && charset[i])
	{
		if (c == charset[i])
			return (0);
		i++;
	}
	return (1);
}

int		ft_status(char c)
{
    static int status = 0;

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

int	ft_default(int *state, char *s, char *charset)
{
	int	i;
	
	i = 0;
	while (s[i] && check(s[i], charset) == 0)
		i++;
	while (s[i] && check(s[i], charset))
	{
		*state = ft_status(*s);
		if (*state != 0)
			break;
		i++;
	}
	return (i);
}

int	ft_quotes(int *state, char *s, char *charset)
{
	int	i;
	
	i = 0;
	if (s && s[i] == 34 || s[i] == 39)
	{
		*state = ft_status(s[i]);
		i++;
	}
	while(s && s[i])
	{
		*state = ft_status(s[i]);
		if (*state == 0)
		{
			i++;
			break;
		}
		i++;
	}
	return (i);
}


int	ft_count(char *s, char *charset)
{
	int	state;
	int	i;
	int	count;

	if (s)
		state = ft_status(s[0]);
	i = 0;
	count = 0;
	while (s && *s)
	{
		if (state == 0)
		{
			i += ft_default(&state, &s[i], charset);
			count++;
		}
		if (state == 1 || state == 2)
		{
			i += ft_quotes(&state, &s[i], charset);
			count++;	
		}
	}
	return (count);
}


int	main(void)
{
	char *s = "'h' awk";
	int	state = 0;
	char *charset = " ";
	char *s1 = "'je'";
	int	nb = 0;
	// nb += ft_quotes(&state, s, charset);
	// s++;
	// nb += ft_quotes(&state, &s1, charset);
	// printf("%d\n", nb);
	printf("%d\n", ft_count(s, charset));
}















// int	ft_default(int *state, char **s, char *charset)
// {
// 	while (**s && check(**s, charset) == 0)
// 		(*s)++;
// 	while (**s && check(**s, charset))
// 	{
// 		*state = ft_status(**s);
// 		if (*state != 0)
// 		{
// 			// printf("returning default string:%s, status : %d\n", *s, *state);
// 			break;
// 			// return (0);		
// 		}
// 		(*s)++;
// 	}
// 	while (**s && check(**s, charset) == 0)
// 		(*s)++;
// 	*state = ft_status(**s);
// 	(*s)++;
// 	// printf("returning default string:%s, status : %d\n", *s, *state);
// 	return (1);
// }

// int	ft_quotes(int *state, char **s, char *charset)
// {
// 	// printf("quotes string:%s, status : %d\n", *s, *state);
// 	while (**s)
// 	{
// 		*state = ft_status(**s);
// 		if (*state == 0)
// 			break;
// 		(*s)++;
// 	}
// 	(*s)++;
// 	// printf("quotes return string:%s, status : %d\n", *s, *state);
// 	if (*state == 0)
// 		return (1);
// 	return (0);
// }
