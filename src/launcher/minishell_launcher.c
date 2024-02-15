/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 10:50:25 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/22 22:01:42 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_launcher.h"

static void	launcher_3(t_ast *node)
{
	if (ft_strcmp("./minishell", node->argv[0]))
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	if (!(ft_strcmp("..", node->argv[0])))
	{
		print_error(PREFIX, "..", "command not found");
		free_and_exit(node->root_node, 127);
	}
	execve(node->path, node->argv, node->env);
	free_and_exit(node->root_node, 0);
}

static void	launcher_2(t_ast *node)
{
	errno = 0;
	if (node->argv && node->argv[0][0] != '.' && node ->argv[0][0] != '/')
	{
		node->path = get_path_location(node->argv[0], node->args->arg,
				node->env, node);
	}
	else if (node->argv && node->argv[0])
	{
		node->path = ft_strdup(node->argv[0]);
		if (!node->path)
			exit_malloc_fail(node->root_node);
		verify_command(node);
	}
	if (!(node->args) && (node->infiles || node->outfiles))
		free_and_exit(node->root_node, 0);
	if ((!(node->path)) && errno == ENOMEM)
		launcher_fail(node->root_node, NULL, STRERROR, 1);
	if (!(node->path))
		launcher_fail(node->root_node, "", "command not found", 127);
	launcher_3(node);
}

void	launcher(t_ast *node)
{
	ch_dir(USE_FILE, node->cwd_file, node->root_dir);
	if (expand_env_file(node))
		free_and_exit(node->root_node, 1);
	prelim_checks(node);
	expander(node, &(node->args), 0);
	expander(node, &(node->infiles), 1);
	expander(node, &(node->outfiles), 1);
	node->argc = arg_list_len(node->args);
	errno = 0;
	node->argv = arg_list_to_str_arr(node->args);
	if ((!(node->argv)) && errno == ENOMEM)
		launcher_fail(node->root_node, NULL, STRERROR, 1);
	set_redirections(node);
	split_args(node);
	check_builtin(node);
	no_path_var_handler(node);
	launcher_2(node);
}
