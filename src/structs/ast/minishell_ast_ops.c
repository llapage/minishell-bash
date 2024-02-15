/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ast_ops.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:27:23 by mde-clee          #+#    #+#             */
/*   Updated: 2023/08/31 14:53:51 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_ast.h"

t_ast	*ast_lst_last(t_ast *head)
{
	t_ast	*last;

	last = head;
	while (last && last->next)
		last = last->next;
	return (last);
}

void	ast_push_bottom(t_ast **head, t_ast *node)
{
	t_ast	*stack_ptr;

	stack_ptr = *head;
	if (node)
	{
		while (stack_ptr && stack_ptr->next)
			stack_ptr = stack_ptr->next;
		if (stack_ptr)
			stack_ptr->next = node;
		else
			*head = node;
	}
}

void	ast_push(t_ast **dest_head, t_ast **src_head)
{
	t_ast	*node_ptr;

	node_ptr = *src_head;
	*src_head = (*src_head)->next;
	node_ptr->next = *dest_head;
	*dest_head = node_ptr;
}

t_ast	*ast_pop(t_ast **head)
{
	t_ast	*node_ptr;

	node_ptr = *head;
	if (*head)
		*head = (*head)->next;
	return (node_ptr);
}
