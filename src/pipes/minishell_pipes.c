/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_pipes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 11:30:14 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/17 16:52:48 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_pipes.h"

static void	set_input_pipes(t_ast *node,
		int pipe_input_fd,
		int in_subshell)
{
	if (node->type == E_COMMAND)
	{
		node->pipe_end = 1;
		node->input_fd = pipe_input_fd;
	}
	else if (node->type == E_SUBSHELL && __APPLE__)
		set_input_pipes(node->right, pipe_input_fd, 1);
	else if (node->type == E_SUBSHELL && !__APPLE__)
		set_input_pipes(node->left, pipe_input_fd, 1);
	else if ((!(in_subshell)) && __APPLE__)
		set_input_pipes(node->right, pipe_input_fd, in_subshell);
	else if ((!(in_subshell)) && !__APPLE__)
		set_input_pipes(node->left, pipe_input_fd, in_subshell);
	else if (in_subshell)
		set_input_pipes(node->left, pipe_input_fd, in_subshell);
}

static void	set_output_pipes(t_ast *node,
		int pipe_output_fd,
		int in_subshell)
{
	if (node->type == E_COMMAND)
	{
		node->non_blocking = 1;
		node->output_fd = pipe_output_fd;
	}
	else if (node->type == E_SUBSHELL && __APPLE__)
	{
		node->no_fork = 1;
		set_output_pipes(node->right, pipe_output_fd, 1);
	}
	else if (node->type == E_SUBSHELL && !__APPLE__)
	{
		node->no_fork = 1;
		set_output_pipes(node->left, pipe_output_fd, 1);
	}
	else
	{
		if (node->type == E_AND || node->type == E_OR)
			node->non_blocking = 1;
		set_output_pipes(node->right, pipe_output_fd, in_subshell);
	}
}

int	create_pipes(t_ast *node, t_int_list **pipe_list)
{
	int			pipe_fds[2];
	t_int_list	*int_node;

	if (!(node))
		return (0);
	create_pipes(node->left, pipe_list);
	create_pipes(node->right, pipe_list);
	if (node->type == E_PIPE)
	{
		if (pipe(pipe_fds) == -1)
			pipe_fail(node->root_node, NULL, STRERROR, SYSTEM_FAILURE);
		set_output_pipes(node->left, pipe_fds[1], 0);
		set_input_pipes(node->right, pipe_fds[0], 0);
		node->output_fd = pipe_fds[1];
		node->input_fd = pipe_fds[0];
		int_node = int_list_create(pipe_fds[0]);
		if (!(int_node))
			return (ENOMEM);
		int_list_add(pipe_list, int_node);
		int_node = int_list_create(pipe_fds[1]);
		if (!(int_node))
			return (ENOMEM);
		int_list_add(pipe_list, int_node);
	}
	return (0);
}

int	close_pipes(t_int_list	*pipe_list)
{
	t_int_list	*pipe_list_ptr;

	pipe_list_ptr = pipe_list;
	while (pipe_list_ptr)
	{
		if (close(pipe_list_ptr->data) == -1)
			return (-1);
		pipe_list_ptr = pipe_list_ptr->next;
	}
	return (0);
}

void	link_pipe_list(t_ast *node, t_int_list *pipe_list)
{
	if (!(node))
		return ;
	node->pipe_list = pipe_list;
	link_pipe_list(node->left, pipe_list);
	link_pipe_list(node->right, pipe_list);
}
