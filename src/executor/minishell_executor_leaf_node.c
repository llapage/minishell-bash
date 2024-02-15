/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor_leaf_node.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:24:54 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 14:32:48 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_executor.h"

static void	pipe_end_parent(t_ast*node, int pid)
{
	int	wstatus;
	int	exit_status;

	close_pipes(node->pipe_list);
	waitpid(pid, &wstatus, 0);
	while (wait(NULL) > 0)
		;
	exit_status = -1;
	if (WIFEXITED(wstatus))
		exit_status = WEXITSTATUS(wstatus);
	free_and_exit(node->root_node, exit_status);
}

static void	non_pipe_parent(t_ast*node, int pid)
{
	int	wstatus;
	int	exit_status;

	close_pipes(node->pipe_list);
	waitpid(pid, &wstatus, 0);
	exit_status = -1;
	if (WIFEXITED(wstatus))
		exit_status = WEXITSTATUS(wstatus);
	if (WIFSIGNALED(wstatus))
	{
		exit_status = WTERMSIG(wstatus);
		if (exit_status == 2)
			if (ft_pputstr_fd("\n", 1) == -1)
				free_and_exit(node->root_node, 1);
		if (exit_status == 3)
			if (ft_pputstr_fd("Quit: 3\n", 1) == -1)
				free_and_exit(node->root_node, 1);
		exit_status += 128;
	}
	free_and_exit(node->root_node, exit_status);
}

void	leaf_node_handler(t_ast *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		launcher_fail(node->root_node, NULL, STRERROR, SYSTEM_FAILURE);
	else if (pid == 0)
	{
		launcher(node);
		exit (-1);
	}
	else if (node->non_blocking)
		;
	else if (node->pipe_end)
		pipe_end_parent(node, pid);
	else
		non_pipe_parent(node, pid);
}
