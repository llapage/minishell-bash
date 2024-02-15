/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_arg_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:27:26 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 16:57:40 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_arg_list.h"

size_t	arg_list_len(t_arg_list *arg)
{
	t_arg_list	*node_ptr;
	size_t		len;

	node_ptr = arg;
	len = 0;
	while (node_ptr)
	{
		len++;
		node_ptr = node_ptr->next;
	}
	return (len);
}

void	arg_list_clear(t_arg_list **head)
{
	t_arg_list	*next_ptr;
	t_arg_list	*arg_ptr;

	arg_ptr = *head;
	while (arg_ptr)
	{
		next_ptr = arg_ptr->next;
		char_list_clear(&arg_ptr->arg);
		free(arg_ptr);
		arg_ptr = NULL;
		arg_ptr = next_ptr;
	}
	*head = NULL;
}

void	arg_list_remove(t_arg_list **args, t_arg_list *arg)
{
	t_arg_list	*arg_list_ptr;
	t_arg_list	*arg_prev_ptr;

	if ((!(*args)) || (!(arg)))
		return ;
	arg_list_ptr = *args;
	arg_prev_ptr = NULL;
	while (arg_list_ptr && arg_list_ptr != arg)
	{
		arg_prev_ptr = arg_list_ptr;
		arg_list_ptr = arg_list_ptr->next;
	}
	if (!(arg_list_ptr))
		return ;
	if (arg_prev_ptr)
		arg_prev_ptr->next = arg_list_ptr->next;
	else
		*args = (*args)->next;
	char_list_clear(&arg->arg);
	free(arg);
}

int	arg_list_insert(t_arg_list **args, t_arg_list *ptr, t_char_list *arg)
{
	t_arg_list	*new_arg_node;
	t_arg_list	*arg_list_ptr;
	t_arg_list	*tmp;

	new_arg_node = malloc(sizeof(t_arg_list));
	if (!(new_arg_node))
	{
		errno = ENOMEM;
		return (-1);
	}
	new_arg_node->split = 1;
	new_arg_node->arg = arg;
	arg_list_ptr = *args;
	while (arg_list_ptr && arg_list_ptr != ptr)
		arg_list_ptr = arg_list_ptr->next;
	tmp = NULL;
	if (arg_list_ptr)
	{
		tmp = arg_list_ptr->next;
		arg_list_ptr->next = new_arg_node;
	}
	else
		*args = new_arg_node;
	new_arg_node->next = tmp;
	return (0);
}

int	arg_list_add(t_arg_list **args, t_char_list *arg)
{
	t_arg_list	*new_arg_node;
	t_arg_list	*arg_list_ptr;

	new_arg_node = malloc(sizeof(t_arg_list));
	if (!(new_arg_node))
	{
		errno = ENOMEM;
		return (-1);
	}
	new_arg_node->split = 0;
	new_arg_node->arg = arg;
	arg_list_ptr = *args;
	while (arg_list_ptr && arg_list_ptr->next)
		arg_list_ptr = arg_list_ptr->next;
	if (arg_list_ptr)
		arg_list_ptr->next = new_arg_node;
	else
		*args = new_arg_node;
	new_arg_node->next = NULL;
	return (0);
}
