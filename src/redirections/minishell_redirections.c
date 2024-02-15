/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:30:31 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 16:06:49 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_redirections.h"

static void	set_redirection_output_fd(t_ast *node)
{
	if (dup2(node->output_fd, STDOUT_FILENO) == -1)
	{
		print_error(PREFIX, NULL, strerror(errno));
		free_and_exit(node->root_node, SYSTEM_FAILURE);
	}
	if (close_pipes(node->pipe_list) == -1)
	{
		print_error(PREFIX, NULL, strerror(errno));
		free_and_exit(node->root_node, SYSTEM_FAILURE);
	}
}

void	set_redirections(t_ast *node)
{
	if (node->outfiles)
		handle_pipe_outfiles(node);
	if (node->infiles)
		handle_pipe_infiles(node);
	if (node->input_fd != STDIN_FILENO)
	{
		if (dup2(node->input_fd, STDIN_FILENO) == -1)
		{
			print_error(PREFIX, NULL, strerror(errno));
			free_and_exit(node->root_node, SYSTEM_FAILURE);
		}
		if (node->output_fd == STDOUT_FILENO)
		{
			if (close_pipes(node->pipe_list) == -1)
			{
				print_error(PREFIX, NULL, strerror(errno));
				free_and_exit(node->root_node,
					SYSTEM_FAILURE);
			}
		}
	}
	if (node->output_fd != STDOUT_FILENO)
		set_redirection_output_fd(node);
}
