/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:56:58 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/03 11:46:12 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int	ft_status(char c, int reset)
{
	static int	status = 0;
	
	if (reset == 1)
		status = 0;
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

int	check_sep(char c, char b)
{
	char	*sep;
	int		i;

	sep = " >|<";
	i = 0;
	while (sep[i])
	{
		if (sep[i] == c || sep[i] == b)
			return (1);
		i++;
	}
	return (0);
}

int	ft_len(char *s, int *j)
{
	int	len;
	int	state;

	while (s[*j] == ' ')
		(*j)++;
	state = 0;
	len = 0;
	if (!ft_strncmp(&s[len + *j], ">>", 2)
		|| !ft_strncmp(&s[len + *j], "<<", 2))
		return (2);
	while (s[len + *j])
	{
		state = ft_status(s[len + *j], 0);
		len++;
		if (check_sep(s[len + *j], s[len + *j -1]) && state == 0)
			break ;
	}
	return (len);
}

char	*ft_args(char *s)
{
	int			len;
	char		*res;
	int			i;
	static int	j = 0;

	if (!s || (s && s[j] == 0))
		return (NULL);
	while (s[j] == ' ')
		j++;
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

t_token	*make_token(char *s)
{
	t_token	*token;
	char	*res;

	res = ft_args(s);
	token = t_lstnew(res, 0);
	while (res != NULL)
	{
		res = ft_args(s);
		if (res != NULL)
			t_lstadd_back(&token, t_lstnew(res, 0));
	}
	return (token);
}
