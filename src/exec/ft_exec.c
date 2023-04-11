/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:27:34 by tedelin           #+#    #+#             */
/*   Updated: 2023/04/11 09:43:01 by mcatal-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_cmd *cmd)
{
	char	*line;
	int 	cpy;

	cpy = dup(0);
	cmd->in = open(".tmp", O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (cmd->in == -1)
		return ;
	ft_signal(HERE_DOC);
	while (1)
	{
		line = readline(">");
		if (!line || (ft_strncmp(cmd->red->value, line,
			ft_strlen(cmd->red->value)) == 0
			&& (ft_strlen(line) == ft_strlen(cmd->red->value))) || g_exit == 130)
		{
			// fprintf(stderr, "g_exit = %d\n", g_exit);
			if (g_exit == 0 && !line)
				fprintf(stderr, "minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", cmd->red->value);
			free(line);
			dup2(cpy, 0);
			// ft_signal(IGNORE);
			break ;
		}
		line = ft_dollar(line, 2);
		ft_putendl_fd(line, cmd->in);
		free(line);
	}
	close(cmd->in);
	if (g_exit == 130)
		cmd->in = open("/dev/null", O_RDONLY);
	else
		cmd->in = open(".tmp", O_RDONLY);	
}
void	close_before(t_cmd *cmd, int type)
{
	if (type == RIN && cmd->in > 2)
		close(cmd->in);
	else if (type == ROUT && cmd->out > 2)
		close(cmd->out);
	else if (type == DRIN && cmd->in > 2)
		close(cmd->in);
	else if (type == DROUT && cmd->out > 2)
		close(cmd->out);
}

void	red_loop(t_token *red, t_cmd *cur)
{
	while (red)
	{
		close_before(cur, red->type);
		if (red->type == RIN)
			cur->in = open(red->value, O_RDONLY);
		else if (red->type == ROUT)
			cur->out = open(red->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (red->type == DRIN)
			ft_heredoc(cur);
		else if (red->type == DROUT)
			cur->out = open(red->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cur && (cur->in == -1 || cur->out == -1))
		{
			perror(red->value);
			break ;
		}
		if (cur)
			red = red->next;
	}
}

void	make_red(t_cmd **lst)
{
	t_cmd	*cur;
	t_token	*red;

	cur = *lst;
	while (cur)
	{
		cur->in = -2;
		cur->out = -2;
		red = cur->red;
		red_loop(red, cur);
		if (cur)
			cur = cur->next;
	}
}

int	launch_exec(t_cmd **lst)
{
	t_cmd	*cur;
	t_pid	*lst_pid;

	cur = *lst;
	lst_pid = NULL;
	make_red(lst);
	if (!lst)
		return (0);
	if (!cur->next && !is_builtin_no_child(cur, lst))
	{
		free_cmd(lst);
		return (0);
	}
	while (cur)
	{
		ft_process(cur, &lst_pid, lst);
		cur = cur->next;
	}
	ft_wait(lst_pid);
	unlink(".tmp");
	free_cmd(lst);
	return (0);
}
