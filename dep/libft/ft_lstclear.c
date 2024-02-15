/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 19:32:01 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/11 17:13:17 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*prev_node;

	if ((!(lst)) || (!(del)))
		return ;
	while (*lst)
	{
		prev_node = *lst;
		*lst = prev_node->next;
		del(prev_node->content);
		free(prev_node);
	}
}
