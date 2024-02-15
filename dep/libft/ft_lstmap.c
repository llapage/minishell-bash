/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 20:03:03 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/11 17:08:10 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mapped_list;
	t_list	*node;

	if ((!(f)) || (!(del)))
		return (0);
	mapped_list = 0;
	while (lst)
	{
		node = malloc(sizeof(t_list));
		if (!(node))
		{
			ft_lstclear(&mapped_list, del);
			return (0);
		}
		node->content = f(lst->content);
		node->next = 0;
		ft_lstadd_back(&mapped_list, node);
		lst = lst->next;
	}
	return (mapped_list);
}
