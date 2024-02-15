/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor_and_or_node.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:22:58 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 14:32:48 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_executor.h"

static void	and_or_node_handler_3(int pid, t_ast *node, int exit_status)
{
	int	wstatus;

	waitpid(pid, &wstatus, 0);
	if (WIFEXITED(wstatus))
		exit_status = WEXITSTATUS(wstatus);
	free_tree(node->root_node);
	exit (exit_status);
}

static void	and_or_node_handler_2(t_ast *node, int exit_status)
{
	pid_t	pid;

	check_exit_code(node->root_node, NULL, &exit_status);
	if (((node->type == E_AND && (!(exit_status)))
			|| (node->type == E_OR
				&& exit_status)) && (!(node->non_blocking)))
	{
		pid = fork();
		if (pid == -1)
			launcher_fail(node->root_node, NULL, STRERROR, SYSTEM_FAILURE);
		else if (pid == 0)
			executor_main(node->right);
		else
			and_or_node_handler_3(pid, node, exit_status);
	}
	else
	{
		if (!(node->non_blocking))
			free_and_exit(node->root_node, exit_status);
		else if (((node->type == E_AND && (!(exit_status)))
				|| (node->type == E_OR
					&& exit_status)))
			executor_main(node->right);
	}
}

void	and_or_node_handler(t_ast *node)
{
	pid_t	pid;
	int		wstatus;
	int		exit_status;

	exit_status = 1;
	pid = fork();
	if (pid == -1)
		launcher_fail(node->root_node, NULL, STRERROR, SYSTEM_FAILURE);
	else if (pid == 0)
	{
		executor_main(node->left);
		exit (-1);
	}
	else
	{
		if (!(node->non_blocking))
			close_pipes(node->pipe_list);
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))
			exit_status = WEXITSTATUS(wstatus);
	}
	and_or_node_handler_2(node, exit_status);
}
