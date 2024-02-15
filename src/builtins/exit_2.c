/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:16:56 by llapage           #+#    #+#             */
/*   Updated: 2023/10/17 16:50:26 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_builtins.h"

static int	forced_exit(t_ast *root_node)
{
	int		fd;
	char	*exit_code;
	char	*file_name;

	file_name = ft_strjoin(root_node->root_dir,
			"/.cache/.minishell_exit_code");
	if (access(file_name, F_OK))
	{
		free(file_name);
		return (0);
	}
	fd = open(file_name, O_RDONLY);
	free(file_name);
	if (fd == -1)
		free_and_exit(root_node, 1);
	exit_code = get_next_line(fd);
	if (close(fd) == -1
		|| *exit_code == '!')
	{
		free(exit_code);
		return (1);
	}
	free(exit_code);
	return (0);
}

static void	write_int_exit_code(t_ast *root_node, int exit_code)
{
	char	*exit_str;

	if (g_exit_code)
		exit_code = g_exit_code;
	exit_str = ft_itoa(exit_code);
	if (!(exit_str))
		exit_malloc_fail(root_node);
	if (write_exit_code(exit_str, root_node->root_dir) == -1)
	{
		free(exit_str);
		print_error(PREFIX, NULL, STRERROR);
		free_and_exit(root_node, SYSTEM_FAILURE);
	}
	free(exit_str);
}

void	free_and_exit(t_ast *root_node, int exit_code)
{
	if (exit_code == SYSTEM_FAILURE && root_node)
	{
		if (write_exit_code("!1", root_node->root_dir) == -1)
		{
			print_error(PREFIX, NULL, STRERROR);
			exit_code = EXIT_FAILURE;
		}
	}
	else if (!(forced_exit(root_node)) && root_node)
		write_int_exit_code(root_node, exit_code);
	if (root_node)
		free_tree(root_node);
	if (g_exit_code)
		exit(g_exit_code);
	exit(exit_code);
}

int	too_much_arguments(int *ret, char *root_dir)
{
	*ret = ft_pputstr_fd("Minishell: exit: too many arguments\n", 1);
	if (*ret)
	{
		write_exit_code("!1", root_dir);
		return (SYSTEM_FAILURE);
	}
	write_exit_code("?1", root_dir);
	return (EXIT_FAILURE);
}
