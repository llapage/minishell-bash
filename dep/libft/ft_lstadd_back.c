/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:43:47 by mde-clee          #+#    #+#             */
/*   Updated: 2023/05/11 17:13:00 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_ptr;

	if (!(lst))
		return ;
	if (*lst)
	{
		lst_ptr = *lst;
		while (lst_ptr && lst_ptr->next)
			lst_ptr = lst_ptr->next;
		lst_ptr->next = new;
	}
	else
		*lst = new;
}
