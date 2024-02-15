/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_redirections_open_files.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 09:55:03 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 10:01:14 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_redirections.h"

static void	open_files_fail(t_ast *node, char *file, char *path)
{
	free(path);
	print_error(PREFIX, file, STRERROR);
	free_and_exit(node->root_node, EXIT_FAILURE);
}

static void	open_files_2(t_ast *node, t_arg_list **arg_ptr, char *path,
			char *file)
{
	int	fd;

	fd = -1; 
	if ((*arg_ptr)->mode == APPEND)
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	else if ((*arg_ptr)->mode == TRUNCATE)
		fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	free(file);
	if (fd == -1) 
		open_files_fail(node, file, path);
	if (close(fd) == -1) 
		open_files_fail(node, file, path);
	*arg_ptr = (*arg_ptr)->next;
}

void	open_files(t_ast *node, t_arg_list **arg_ptr, char *path)
{
	char	*tmp;
	char	*file;

	tmp = char_list_to_str((*arg_ptr)->arg);
	if (!(tmp))
	{
		free(path);
		exit_malloc_fail(node->root_node);
	}
	if (path)
	{
		file = ft_strjoin(path, tmp);
		free (tmp);
	}
	else
		file = tmp;
	if (!(file))
	{
		free(path);
		exit_malloc_fail(node->root_node);
	}
	open_files_2(node, arg_ptr, path, file);
}
