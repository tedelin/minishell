/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:00:42 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/28 13:43:42 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset && charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static	int	ft_count(const char *str, char *charset)
{
	int	words;

	if (!str)
		return (0);
	words = 0;
	while (str && *str)
	{
		if (is_charset(*str, charset) == 0)
		{
			words++;
			while (is_charset(*str, charset) == 0 && *str)
				str++;
		}
		else
			str++;
	}
	return (words);
}

static	char	*ft_wordadd(const char *s, char *charset)
{
	int		len;
	int		i;
	char	*word;

	len = 0;
	i = 0;
	while (s && is_charset(s[len], charset) == 0 && s[len])
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (word)
	{
		while (s && s[i] && i < len)
		{
			word[i] = s[i];
			i++;
		}
		word[i] = '\0';
	}
	return (word);
}

void	free_tab(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(tab[i++]);
	free(tab);
}

void		ft_status(int *status, char c)
{
	if (c == '\'' && *status == 0)
		*status = 1;
	else if (c == '\"' && *status == 0)
		*status = 2;
	else if (status == 1 && c == '\'')
		status = 0;
	else if (status == 2 && c == '\"')
		status = 0;
	return (*status);
}

char	**split_operators(char const *s, char *charset)
{
	int			i;
	int			j;
	char		**tab;
	int			status;

	i = -1;
	j = -1;
	tab = (char **)malloc(sizeof(char *) * (ft_count(s, charset) + 1));
	if (!tab)
		return (NULL);
	while (s && s[++i])
	{
		ft_status(&status, s[i]);
		if (is_charset(s[i], charset) == 0 && status == 0)
		{
			tab[++j] = ft_wordadd(&s[i], charset);
			if (!tab[j])
				return (free_tab(tab, j), NULL);
			while (is_charset(s[i], charset) == 0 && s[i])
				i++;
		}
	}
	tab[j] = 0;
	return (tab);
}
