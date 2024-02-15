/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_finalizer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 08:37:34 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 10:07:57 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_finalizer.h"

static void	count_args(t_ast *nodes)
{
	int			count;
	t_arg_list	*arg_ptr;
	t_ast		*node_ptr;

	node_ptr = nodes;
	while (node_ptr)
	{
		count = -1;
		arg_ptr = nodes->args;
		while (arg_ptr)
		{
			count++;
			arg_ptr = arg_ptr->next;
		}
		nodes->nbr_args = count;
		node_ptr = node_ptr->next;
	}
}

int	finalizer(t_ast *nodes, char *root_dir)
{
	t_int_list	*pipe_list;

	pipe_list = NULL;
	count_args(nodes);
	if (set_various(nodes, nodes, 0, root_dir)
		|| create_pipes(nodes, &pipe_list))
	{
		free_tree(nodes);
		print_error(PREFIX, NULL, STRERROR);
		exit(EXIT_FAILURE);
	}
	link_pipe_list(nodes, pipe_list);
	return (0);
}
