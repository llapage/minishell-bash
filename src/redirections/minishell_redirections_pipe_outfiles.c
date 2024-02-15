/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirections_pipe_outfiles.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 09:32:12 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/22 06:43:24 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_redirections.h"

static void	handle_pipe_outfiles_2_fail(t_ast *node, char *file, int fail_mode)
{
	print_error(PREFIX, file, STRERROR);
	free(file);
	free_and_exit(node->root_node, fail_mode);
}

static void	handle_pipe_outfiles_3(t_ast *node, char *file)
{
	if (node->output_fd != -1)
	{
		if (dup2(node->output_fd, 1) == -1)
			handle_pipe_outfiles_2_fail(node, file, SYSTEM_FAILURE);
		free(file);
	}
	else
	{
		node->output_fd = STDOUT_FILENO;
		if ((!(access(file, F_OK | W_OK))) && errno != EISDIR)
			handle_pipe_outfiles_2_fail(node, file, SYSTEM_FAILURE);
		handle_pipe_outfiles_2_fail(node, file, EXIT_FAILURE);
	}
}

static void	handle_pipe_outfiles_2(t_ast *node, char *file, char *path,
		int file_mode)
{
	if (file[0] != '/')
		path = ft_strfjoin(path, file);
	else
	{
		free(path);
		path = ft_strdup(file);
	}
	if (!(path))
	{
		free(file);
		exit_malloc_fail(node->root_node);
	}
	errno = 0;
	if (file_mode == APPEND)
		node->output_fd = open(path,
				O_RDWR | O_CREAT | O_APPEND, 0666);
	else
		node->output_fd = open(path,
				O_RDWR | O_CREAT | O_TRUNC, 0666);
	free (path);
	handle_pipe_outfiles_3(node, file);
}

void	handle_pipe_outfiles(t_ast *node)
{
	char		*path;
	char		*file;
	t_arg_list	*arg_ptr;

	path = get_cwd(node->cwd_file, node->root_dir);
	if (!(path))
	{
		print_error(PREFIX, NULL, STRERROR);
		free_and_exit(node->root_node, SYSTEM_FAILURE);
	}
	path = ft_strfjoin(path, "/");
	if (!(path))
		exit_malloc_fail(node->root_node);
	arg_ptr = node->outfiles;
	while (arg_ptr->next)
	{
		if (arg_ptr->arg->character == '/')
			open_files(node, &arg_ptr, NULL);
		else
			open_files(node, &arg_ptr, path);
	}
	file = char_list_to_str(arg_ptr->arg);
	if (!(file))
		free_exit_malloc_fail(node->root_node, path);
	handle_pipe_outfiles_2(node, file, path, arg_ptr->mode);
}
