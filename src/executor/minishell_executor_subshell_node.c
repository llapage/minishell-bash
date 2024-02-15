/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor_subshell_node.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:21:50 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 14:32:48 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_executor.h"

static void	execute_subshell(t_ast *node)
{
	if (__APPLE__)
		executor_main(node->right);
	else
		executor_main(node->left);
}

void	subshell_node_handler(t_ast *node)
{
	pid_t	pid;
	int		wstatus;
	int		exit_status;

	if (node->no_fork)
		return (execute_subshell(node));
	pid = fork();
	if (pid == -1)
		launcher_fail(node->root_node, NULL, STRERROR, SYSTEM_FAILURE);
	else if (pid == 0)
		execute_subshell(node);
	else
	{
		close_pipes(node->pipe_list);
		waitpid(pid, &wstatus, 0);
		exit_status = 1;
		if (WIFEXITED(wstatus))
			exit_status = WEXITSTATUS(wstatus);
		clear_subshell_cache(node->root_dir);
		free_and_exit(node->root_node, exit_status);
	}
}
