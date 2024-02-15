/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:53:09 by llapage           #+#    #+#             */
/*   Updated: 2023/10/17 16:48:39 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_builtins.h"

void	set_exit_code(int exit_code, t_ast *root_node, char *root_dir)
{
	char	*exit_str;

	exit_str = ft_itoa(exit_code);
	if (!(exit_str) && root_node)
		exit_malloc_fail(root_node);
	if (write_exit_code(exit_str, root_dir) == -1)
	{
		free(exit_str);
		print_error(PREFIX, NULL, STRERROR);
		free_and_exit(root_node, EXIT_FAILURE);
	}
	free(exit_str);
}

static void	check_exit_code_2(t_ast *root_node, char *root_dir,
		int *exit_status, char *exit_code)
{
	long long	exit_code_atoll;

	if (*exit_code == '!')
	{
		exit_code_atoll = ft_atoll(exit_code + 1);
		free(exit_code);
		if (root_dir)
			clear_cache(root_dir);
		else
			clear_cache(root_node->root_dir);
		free_and_exit(root_node, exit_code_atoll % 256);
	}
	else if (*exit_code == '?')
		*exit_status = 1;
	else
	{
		*exit_status = ft_atoi(exit_code);
		free(exit_code);
	}
}

static void	check_exit_code_3(char *exit_code)
{
	free (exit_code);
	return ;
}

void	check_exit_code(t_ast *root_node, char *root_dir, int *exit_status)
{
	int		fd;
	char	*exit_code;
	char	*file_name;

	if (root_dir)
		file_name = ft_strjoin(root_dir,
				"/.cache/.minishell_exit_code");
	else
		file_name = ft_strjoin(root_node->root_dir,
				"/.cache/.minishell_exit_code");
	if (access(file_name, F_OK))
	{
		free(file_name);
		*exit_status = 0;
		return ;
	}
	fd = open(file_name, O_RDONLY);
	free(file_name);
	if (fd == -1)
		free_and_exit(root_node, 1);
	exit_code = get_next_line(fd);
	if (close(fd) == -1)
		return (check_exit_code_3(exit_code));
	check_exit_code_2(root_node, root_dir, exit_status, exit_code);
}

int	write_exit_code(char *exit_str, char *root_dir)
{
	int		fd;
	char	*file_name;

	file_name = ft_strjoin(root_dir, "/.cache/.minishell_exit_code");
	if (!(file_name))
		return (error_enomem(-1, NULL, NULL));
	fd = open(file_name, O_RDWR | O_TRUNC | O_CREAT, 0666);
	free(file_name);
	if (fd == -1)
		return (-1);
	if (ft_pputstr_fd(exit_str, fd) == -1)
		return (-1);
	if (close(fd) == -1)
		return (-1);
	return (0);
}
