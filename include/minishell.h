/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:54:32 by tedelin           #+#    #+#             */
/*   Updated: 2023/02/28 10:54:31 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

enum state {dble_quotes = 2, s_quotes = 1, split = 0};

typedef struct s_token
{
	char	*value;
	enum	type;
	struct s_token *next;
}	t_token;

typedef struct s_cmd
{
	t_token *arg;
	t_token *red;
	int	fd_in;
	int	fd_out;
	struct s_cmd *next;
}	t_cmd;

#endif
