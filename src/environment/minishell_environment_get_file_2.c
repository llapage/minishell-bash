/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment_get_file_2.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 10:57:06 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/22 19:20:06 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_environment.h"

static int	copy_parent_shell_env_file_4(t_ast *node, int env_fd,
			int prev_env_fd)
{
	if (file_copy(env_fd, prev_env_fd))
	{
		print_error(PREFIX, NULL, STRERROR);
		if (close(env_fd) == -1)
			print_error(PREFIX, NULL, STRERROR);
		free_and_exit(node->root_node, SYSTEM_FAILURE);
	}
	if (close(env_fd) == -1 || close(prev_env_fd))
	{
		print_error(PREFIX, NULL, STRERROR);
		free_and_exit(node->root_node, SYSTEM_FAILURE);
	}
	env_fd = open(node->env_file, O_RDWR, 0666);
	while (env_fd < 0 && errno == EAGAIN)
		env_fd = open(node->env_file, O_RDWR, 0666);
	if (env_fd == -1)
	{
		print_error(PREFIX, NULL, STRERROR);
		free_and_exit(node->root_node, SYSTEM_FAILURE);
	}
	return (env_fd);
}

static void	copy_parent_shell_env_file_3(t_ast *node, int *prev_shell_id,
				int *prev_env_fd)
{
	char	*prev_shell_id_ascii;
	char	*prev_file_name;
	char	*tmp;

	(*prev_shell_id)--;
	prev_shell_id_ascii = ft_itoa(*prev_shell_id);
	if (!(prev_shell_id_ascii))
		exit_malloc_fail(node->root_node);
	tmp = ft_strjoin(node->root_dir, "/.cache/.minishell_env_");
	if (!(tmp))
	{
		free(prev_shell_id_ascii);
		exit_malloc_fail(node->root_node);
	}
	prev_file_name = ft_strjoin(tmp, prev_shell_id_ascii);
	free(tmp);
	free(prev_shell_id_ascii);
	if (!(prev_file_name))
		exit_malloc_fail(node->root_node);
	*prev_env_fd = open(prev_file_name, O_RDONLY, 0666);
	while (*prev_env_fd < 0 && errno == EAGAIN)
		*prev_env_fd = open(prev_file_name, O_RDONLY, 0666);
	free(prev_file_name);
}

static int	copy_parent_shell_env_file_2(t_ast *node, int env_fd,
		char *prev_file_name)
{
	int		prev_shell_id;
	int		prev_env_fd;

	prev_shell_id = node->shell_id - 1;
	prev_env_fd = open(prev_file_name, O_RDONLY, 0666);
	while (prev_env_fd < 0 && errno == EAGAIN)
		prev_env_fd = open(prev_file_name, O_RDONLY, 0666);
	free(prev_file_name);
	while (prev_env_fd < 0)
	{
		if (prev_shell_id == 0)
		{
			print_error(PREFIX, NULL, STRERROR);
			free_and_exit(node->root_node, SYSTEM_FAILURE);
		}
		copy_parent_shell_env_file_3(node, &prev_shell_id, &prev_env_fd);
	}
	return (copy_parent_shell_env_file_4(node, env_fd, prev_env_fd));
}

int	copy_parent_shell_env_file(t_ast *node, int env_fd)
{
	int		prev_shell_id;
	char	*prev_shell_id_ascii;
	char	*tmp;
	char	*prev_file_name;

	prev_shell_id = node->shell_id - 1;
	prev_shell_id_ascii = ft_itoa(prev_shell_id);
	if (!(prev_shell_id_ascii))
		exit_malloc_fail(node->root_node);
	tmp = ft_strjoin(node->root_dir, "/.cache/.minishell_env_");
	if (!(tmp))
	{
		free(prev_shell_id_ascii);
		exit_malloc_fail(node->root_node);
	}
	prev_file_name = ft_strjoin(tmp, prev_shell_id_ascii);
	free(tmp);
	free(prev_shell_id_ascii);
	if (!(prev_file_name))
		exit_malloc_fail(node->root_node);
	return (copy_parent_shell_env_file_2(node, env_fd, prev_file_name));
}
