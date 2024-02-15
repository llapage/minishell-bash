/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment_expand_file.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 07:12:40 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/28 19:34:03 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_environment.h"

static void	build_string_exit_fail(t_ast *root_node, int fd)
{
	if (close(fd) == -1)
		print_error(PREFIX, NULL, STRERROR);
	exit_malloc_fail(root_node);
}

static void	build_string(t_ast *node, int fd, char **long_string)
{
	char	*tmp;
	char	*next_line;

	*long_string = get_next_line(fd);
	next_line = get_next_line(fd);
	while (next_line)
	{
		tmp = ft_strjoin(*long_string, next_line);
		free(*long_string);
		free(next_line);
		if (!(tmp))
			build_string_exit_fail(node->root_node, fd);
		*long_string = ft_strdup(tmp);
		free(tmp);
		if (!(*long_string))
			build_string_exit_fail(node->root_node, fd);
		next_line = get_next_line(fd);
	}
}

int	expand_env_file(t_ast *node)
{
	int		fd;
	char	*long_string;

	fd = get_env_file(node);
	if (fd > OPEN_MAX)
	{
		print_error(PREFIX, NULL, "Too many open files\n");
		free_and_exit(node->root_node, EXIT_FAILURE);
	}
	build_string(node, fd, &long_string);
	node->env = ft_split(long_string, '\n');
	free(long_string);
	if (close(fd) == -1 || (!(node->env)))
	{
		if (!(node->env))
		{
			errno = ENOMEM;
			if (close(fd) == -1)
				print_error(PREFIX, NULL, STRERROR);
		}
		print_error(PREFIX, NULL, STRERROR);
		free_and_exit(node->root_node, SYSTEM_FAILURE);
	}
	return (0);
}
