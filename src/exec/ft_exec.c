/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <mcatal-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 14:14:42 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/22 14:58:8:03 by mcatal-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_cmd *cmd)
{
	int	len;

	if (!cmd->arg || !cmd->arg->value)
		return (1);
	len = ft_strlen(cmd->arg->value);
	if (!ft_strncmp(cmd->arg->value, "cd", 2) && len == 2)
		return (ft_cd(cmd), 0);
	else if (!ft_strncmp(cmd->arg->value, "echo", 4) && len == 4)
		return (ft_echo(cmd), 0);
	else if (!ft_strncmp(cmd->arg->value, "env", 3) && len == 3)
		return (env_cmd(cmd), 0);
	else if (!ft_strncmp(cmd->arg->value, "export", 6) && len == 6)
		return (ft_export(cmd), 0);
	else if (!ft_strncmp(cmd->arg->value, "pwd", 3) && len == 3)
		return (ft_pwd(0), 0);
	else if (!ft_strncmp(cmd->arg->value, "unset", 5) && len == 5)
		return (ft_unset(cmd), 0);
	else if (!ft_strncmp(cmd->arg->value, "exit", 4) && len == 4)
		return (ft_exit(cmd), 0);
	else
		return (1);
}

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
		tab[i++] = lst->value;
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
		tab[i++] = lst->var;
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	ft_heredoc(t_cmd *cmd)
{
	char	*line;

	
	cmd->in = open("tmpfile.txt", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	while (1)
	{
		line = readline("pipe heredoc>");
		if (!line || (ft_strncmp(cmd->red->value, line, ft_strlen(cmd->red->value)) == 0
				&& (ft_strlen(line) == ft_strlen(cmd->red->value))))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, cmd->in);
		free(line);
	}
}

void	make_red(t_cmd *cmd)
{
	cmd->in = -2;
	cmd->out = -2;
	while (cmd->red)
	{
		if (cmd->red->type == RIN)
			cmd->in = open(cmd->red->value, O_RDONLY);
		else if (cmd->red->type == ROUT)
			cmd->out = open(cmd->red->value, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		else if (cmd->red->type == DRIN)
			ft_heredoc(cmd);
		else if (cmd->red->type == DROUT)
			cmd->out = open(cmd->red->value, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		cmd->red = cmd->red->next;
	}
}

int	launch_exec(t_cmd **lst)
{
	t_cmd	*cur;
	char	**cur_arg;
	t_pid	*lst_pid;

	cur = *lst;
	lst_pid = NULL;
	// printf("%s\n", cur->arg->value);
	while (cur)
	{
		cur_arg = ft_lst_to_tab(cur->arg);
		make_red(cur);
		// if (is_builtin(cur))
		// 	exec_cmd(cur_arg, n++);
		// is_builtin(cur);
		ft_process(cur, &lst_pid);
		// printf("%p\n", cur);
		// tab_free(cur_arg);
		// print_lst(&cur->arg);
		// printf("\n\n\n");
		cur = cur->next;
	}
	return (0);
}
