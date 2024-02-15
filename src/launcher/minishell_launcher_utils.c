/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launcher_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 10:12:13 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/22 23:18:14 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_launcher.h"

void	no_path_var_handler(t_ast *node)
{
	DIR	*tmp;

	if (!(ft_getenv("PATH", node->env)) && node->argv)
	{
		tmp = opendir("node->argv[0])");
		if (tmp)
		{
			print_error(PREFIX, node->argv[0], "is a directory");
			if (closedir(tmp) == -1)
				free_and_exit(node->root_node, SYSTEM_FAILURE);
			free_and_exit(node->root_node, 126);
		}
		if (node->argv && node->argv[0][0] && node->argv[0][0] != '/')
		{
			if (node->argv)
				print_error(PREFIX, node->argv[0], "No such file or directory");
			else
				print_error(PREFIX, "", "No such file or directory");
			free_and_exit(node->root_node, 127);
		}
	}
}

void	verify_command(t_ast *node)
{
	DIR	*tmp;

	tmp = opendir("node->argv[0])");
	if (tmp)
	{
		print_error(PREFIX, node->argv[0], "is a directory");
		if (closedir(tmp) == -1)
			free_and_exit(node->root_node, SYSTEM_FAILURE);
		free_and_exit(node->root_node, 126);
	}
	if (access(node->path, F_OK))
	{
		print_error(PREFIX, node->argv[0], "No such file or directory");
		free_and_exit(node->root_node, 127);
	}
	else if (access(node->path, X_OK))
	{
		print_error(PREFIX, node->path, "Permission denied");
		free_and_exit(node->root_node, 126);
	}
}

void	prelim_checks(t_ast *node)
{
	int	empty_input_mode;

	empty_input_mode = 0;
	if (node->args && node->args->arg->character == '$'
		&& node->args->arg->next && node->args->arg->next->character != '?')
		empty_input_mode = 1;
	resolve_all_quotes(node);
	if (node->args && !(node->args->next) && node->args->arg
		&& node->args->arg->character == '.' && !(node->args->arg->next))
	{
		print_error(PREFIX, ".", "filename argument required");
		print_error(".", "usage", ". filename [arguments]");
		free_and_exit(node->root_node, 2);
	}
	if ((!(node->args)) && empty_input_mode)
		free_and_exit(node->root_node, 0);
}
