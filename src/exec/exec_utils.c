/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:25:05 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/03 13:48:58 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tab_free(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**ft_lst_to_tab(t_token *lst)
{
	char	**tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (t_lstsize(&lst) + 1));
	while (lst)
	{
		tab[i++] = ft_strdup(lst->value);
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}

char	**ft_lst_to_tab_env(t_env *lst)
{
	char	**tab;
	int		i;

	i = 0;
	tab = malloc(sizeof(char *) * (env_lstsize(&lst) + 1));
	while (lst)
	{
		tab[i++] = ft_strdup(lst->var);
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	ft_wait(t_pid *lst)
{
	t_pid	*tmp;

	while (lst)
	{
		waitpid(lst->content, NULL, 0);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
}

void	exit_child(t_cmd **lst_cmd, t_pid **lst, char *msg)
{
	t_pid	*tmp;

	while (*lst)
	{
		tmp = *lst;
		(*lst) = (*lst)->next;
		free(tmp);
	}
	if (ft_strncmp(msg, "main", 4) == 0)
		exit(errno);
	free_cmd(lst_cmd);
	ft_env(NULL, FREE, NULL, NULL);
	perror(msg);
	exit(errno);
}
