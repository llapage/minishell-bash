/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirections_pipe_infiles.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 09:30:40 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/22 06:38:23 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_redirections.h"

static void	get_pipe_infile(char **file, t_arg_list *arg_ptr, char **path,
		t_ast *node)
{
	*file = char_list_to_str(arg_ptr->arg);
	if (!(*file))
		exit_malloc_fail(node->root_node);
	*path = get_cwd(node->cwd_file, node->root_dir);
	if (!(*path))
	{
		free(*file);
		print_error(PREFIX, NULL, STRERROR);
		free_and_exit(node->root_node, SYSTEM_FAILURE);
	}
	*path = ft_strfjoin(*path, "/");
	if (!(*path))
		free_exit_malloc_fail(node->root_node, *file);
	if ((*file)[0] == '/')
	{
		free(*path);
		*path = ft_strdup(*file);
	}
	else
		*path = ft_strfjoin(*path, *file);
	if (!(*path))
		free_exit_malloc_fail(node->root_node, *file);
}

static void	handle_pipe_infiles_system_failure(t_ast *node, char *file)
{
	print_error(PREFIX, file, STRERROR);
	free(file);
	free_and_exit(node->root_node, SYSTEM_FAILURE);
}

static void	handle_pipe_infiles_exit_failure(t_ast *node, char *file)
{
	print_error(PREFIX, file, STRERROR);
	free(file);
	free_and_exit(node->root_node, EXIT_FAILURE);
}

static void	handle_pipe_infiles_2(t_ast *node, char *path, char *file)
{
	node->input_fd = open(path, O_RDONLY);
	free (path);
	if (node->input_fd != -1)
	{
		if (dup2(node->input_fd, 0) == -1)
			handle_pipe_infiles_system_failure(node, file);
		free(file);
	}
	else
	{
		node->input_fd = STDIN_FILENO;
		handle_pipe_infiles_exit_failure(node, file);
	}
}

void	handle_pipe_infiles(t_ast *node)
{
	t_arg_list	*arg_ptr;
	char		*file;
	char		*path;

	arg_ptr = node->infiles;
	while (arg_ptr->next)
		arg_ptr = arg_ptr->next;
	file = NULL;
	path = NULL;
	if (node->heredoc_file)
	{
		path = char_list_to_str(arg_ptr->arg);
		if (!(path))
			exit_malloc_fail(node->root_node);
	}
	else
		get_pipe_infile(&file, arg_ptr, &path, node);
	handle_pipe_infiles_2(node, path, file);
}
