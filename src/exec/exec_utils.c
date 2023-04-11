/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:25:05 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/11 17:38:46 by tedelin          ###   ########.fr       */
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
	int		sigint;

	sigint = 0;
	while (lst)
	{
		waitpid(lst->content, &g_exit, 0);
		if (g_exit == 2 && sigint++ == 0)
			write(2, "\n", 1);
		else if (g_exit == 131 && !lst->next)
			write(2, "Quit (core dumped)\n", 19);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	g_exit = WEXITSTATUS(g_exit);
}

void	exit_child(t_cmd **lst_cmd, t_pid **lst, char *msg)
{
	t_pid	*tmp;
	int		tmp_errno;

	tmp_errno = errno;
	while (lst && *lst)
	{
		tmp = *lst;
		(*lst) = (*lst)->next;
		free(tmp);
	}
	free_cmd(lst_cmd);
	ft_env(NULL, FREE, NULL, NULL);
	rl_clear_history();
	if (msg && ft_strncmp(msg, "main", 4))
		perror(msg);
	exit(tmp_errno);
}
