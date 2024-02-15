/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launcher_get_path.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:49:46 by llapage           #+#    #+#             */
/*   Updated: 2023/10/01 16:37:03 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_launcher.h"

static char	*check_command_error_3(char *command, t_ast *node)
{
	if (access(command, F_OK))
	{
		print_error(PREFIX, command, "No such file or directory");
		free_and_exit(node->root_node, 127);
	}
	else if (access(command, X_OK))
	{
		print_error(PREFIX, command, "Permission denied");
		free_and_exit(node->root_node, 126);
	}
	return (ft_strdup(command));
}

static char	*check_command_error_2(char *command, t_ast *node)
{
	print_error(PREFIX, command, "command not found");
	free_and_exit(node->root_node, 127);
	return (NULL);
}

static char	*check_command_error(char *command, t_ast *node)
{
	struct stat	buf;

	if (command && ft_strchr((const char *)command, '/'))
	{
		stat(command, &buf);
		if (S_ISDIR(buf.st_mode) && !ft_getenv("PATH", node->env))
		{
			print_error(PREFIX, command, "is a directory");
			free_and_exit(node->root_node, 126);
		}
		if (S_ISDIR(buf.st_mode))
		{
			print_error(PREFIX, command, "is a directory");
			free_and_exit(node->root_node, 127);
		}
		else
			return (check_command_error_3(command, node));
	}
	return (check_command_error_2(command, node));
}

char	*join_next_path(char *path_ptr, char *command)
{
	char	*next_path;

	next_path = ft_strdupchr(path_ptr, ':');
	next_path = ft_strfjoin(next_path, "/");
	next_path = ft_strfjoin(next_path, command);
	return (next_path);
}

char	*get_path_location(char *command, t_char_list *arg, char **env,
	t_ast *node)
{
	char	*path_ptr;
	char	*next_path;

	if ((!(env)) || (!(arg)))
		return (NULL);
	path_ptr = ft_getenv("PATH", env);
	while (path_ptr)
	{
		next_path = join_next_path(path_ptr, command);
		if (!(access(next_path, F_OK)))
		{
			if (!(access(next_path, X_OK)))
				return (next_path);
			print_error(PREFIX, command, "Permission denied");
			free(next_path);
			free_and_exit(node->root_node, 126);
		}
		free(next_path);
		path_ptr = ft_strchr(path_ptr, ':');
		if (path_ptr)
			path_ptr++;
	}
	errno = 0;
	return (check_command_error(command, node));
}
