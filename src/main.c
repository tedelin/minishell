/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:09:48 by tedelin           #+#    #+#             */
/*   Updated: 2023/03/14 15:57:12 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	main(void)
// {
// 	char *s;
// 	t_token *token;

// 	s = "echo test'hello hihi'world";
// 	token = make_token(s);
// 	ft_type(&token);
// 	if (ft_parser(&token) == 1)
// 		printf("ERROR\n");
// 	else
// 		printf("SUCESS\n");
// 	while (token)
// 	{
// 		printf("token:%s, type:%d\n", token->value, token->type);
// 		token = token->next;
// 	}
// }

// int main(int ac, char **av, char **env)
// {
// 	// char *s = "\"a'''''b\"";
// 	// if (ft_change(s))
// 	// 	printf("change\n");
// 	// else
// 	// 	printf("no change\n");
// 	t_token *current;
	
// 	current = t_lstnew("< in cat | cat > ot", 0);
// 	new_token(current, NULL);
// 	// printf ("%s\n", ft_("$oui "));
// }


int main(int ac, char **av)
{
	char *input;
	t_token *lst;

	input = readline("minishell$");
	lst = make_token(input);
	ft_type(&lst);
	while (lst)
	{
		printf("%s\n", lst->value);
		printf("%d\n", lst->type);
		lst = lst->next;
	}
}