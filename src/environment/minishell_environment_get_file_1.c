/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment_get_file_1.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 10:37:45 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/17 11:41:00 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_environment.h"

static int	get_existing_env_file(t_ast *node)
{
	int		env_fd;

	env_fd = open(node->env_file, O_RDWR, 0666);
	while (env_fd == -1 && errno == EAGAIN)
		env_fd = open(node->env_file, O_RDWR, 0666);
	if (env_fd == -1)
	{
		print_error(PREFIX, NULL, STRERROR);
		free_and_exit(node->root_node, SYSTEM_FAILURE);
	}
	return (env_fd);
}

static int	get_env_file_root_shell(t_ast *node)
{
	int		env_fd;

	env_fd = open(node->env_file, O_RDWR | 0666);
	while (env_fd == -1 && errno == EAGAIN)
		env_fd = open(node->env_file, O_RDWR | 0666);
	if (env_fd == -1)
	{
		print_error(PREFIX, NULL, STRERROR);
		free_and_exit(node->root_node, SYSTEM_FAILURE);
	}
	return (env_fd);
}

int	get_env_file(t_ast *node)
{
	int		env_fd;

	if (node->shell_id == 0)
		return (get_env_file_root_shell(node));
	env_fd = open(node->env_file, O_CREAT | O_EXCL | O_RDWR, 0666);
	while (env_fd == -1 && errno == EAGAIN)
		env_fd = open(node->env_file, O_CREAT | O_EXCL | O_RDWR, 0666);
	if (env_fd == -1 && errno == EEXIST)
		return (get_existing_env_file(node));
	if (env_fd == -1)
	{
		print_error(PREFIX, NULL, STRERROR);
		free_and_exit(node->root_node, SYSTEM_FAILURE);
	}
	return (copy_parent_shell_env_file(node, env_fd));
}
