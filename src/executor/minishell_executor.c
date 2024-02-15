/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 08:58:15 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/17 16:22:57 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_executor.h"

void	executor_main(t_ast *node)
{
	if (!(node))
		return ;
	if (node->type == E_SUBSHELL)
		subshell_node_handler(node);
	else if (node->type == E_AND
		|| node->type == E_OR)
		and_or_node_handler(node);
	else if (node->type == E_PIPE)
		pipe_node_handler(node);
	else
		leaf_node_handler(node);
}

static int	executor_parent(t_ast *root_node, char *root_dir, int pid)
{
	int		exit_status;
	int		wstatus;

	close_pipes(root_node->pipe_list);
	waitpid(pid, &wstatus, 0);
	sig_handler_init();
	exit_status = g_exit_code;
	if (!(exit_status))
	{
		if (WIFEXITED(wstatus) && !exit_status)
			exit_status = WEXITSTATUS(wstatus);
		check_exit_code(root_node, root_dir, &exit_status);
	}
	set_exit_code(exit_status, root_node, root_dir);
	clear_subshell_cache(root_dir);
	free_tree(root_node);
	return (exit_status);
}

int	executor(t_ast *root_node, char **env, char *root_dir)
{
	pid_t	pid;

	if (create_env_file(env, root_dir))
		launcher_fail(root_node, NULL, STRERROR, SYSTEM_FAILURE);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		launcher_fail(root_node, NULL, STRERROR, SYSTEM_FAILURE);
	else if (pid == 0)
	{
		executor_main(root_node);
		exit (-1);
	}
	else
		return (executor_parent(root_node, root_dir, pid));
	return (-1);
}
