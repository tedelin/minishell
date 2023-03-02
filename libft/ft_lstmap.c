/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:50:34 by tedelin           #+#    #+#             */
/*   Updated: 2022/11/18 14:56:36 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*tmp_new;

	if (!lst || !f || !del)
		return (NULL);
	lst_new = ft_lstnew(f(lst->content));
	tmp_new = lst_new;
	if (lst_new)
	{
		while (lst->next)
		{
			tmp_new->next = ft_lstnew(f(lst->next->content));
			if (!tmp_new->next)
			{
				ft_lstclear(&lst_new, del);
				return (NULL);
			}
			tmp_new = tmp_new->next;
			lst = lst->next;
		}
	}
	return (lst_new);
}
