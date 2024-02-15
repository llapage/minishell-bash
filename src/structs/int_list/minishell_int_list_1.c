/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_int_list_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:16:28 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/17 19:26:25 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_int_list.h"

t_int_list	*int_list_create(int data)
{
	t_int_list	*int_node;

	int_node = malloc(sizeof(t_int_list));
	if (!(int_node))
	{
		errno = ENOMEM;
		return (NULL);
	}
	int_node->data = data;
	int_node->next = NULL;
	return (int_node);
}

void	int_list_clear(t_int_list **head)
{
	t_int_list	*next_ptr;
	t_int_list	*lst_ptr;

	if (!(head))
		return ;
	if (!(*head))
		return ;
	lst_ptr = *head;
	while (lst_ptr)
	{
		next_ptr = lst_ptr->next;
		free(lst_ptr);
		lst_ptr = NULL;
		lst_ptr = next_ptr;
	}
	*head = NULL;
}

void	int_list_add(t_int_list **head, t_int_list *new_node)
{
	t_int_list	*lst_ptr;

	if (*head)
	{
		lst_ptr = *head;
		while (lst_ptr && lst_ptr->next)
			lst_ptr = lst_ptr->next;
		lst_ptr->next = new_node;
	}
	else
		*head = new_node;
}

int	int_list_print(t_int_list *head)
{
	t_int_list	*lst_ptr;

	lst_ptr = head;
	while (lst_ptr)
	{
		if (ft_putnbr_base_fd(lst_ptr->data, 10, 1) == -1)
			return (-1);
		lst_ptr = lst_ptr->next;
	}
	return (0);
}
