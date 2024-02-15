/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:54:44 by llapage           #+#    #+#             */
/*   Updated: 2023/10/16 14:32:48 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_errors.h"

void	launcher_fail(t_ast *root_node, char *msg_part_1,
		char *msg_part_2, int exit_code)
{
	print_error(PREFIX, msg_part_1, msg_part_2);
	free_and_exit(root_node, exit_code);
}

void	exit_malloc_fail(t_ast *root_node)
{
	errno = ENOMEM;
	print_error(PREFIX, NULL, STRERROR);
	free_and_exit(root_node, SYSTEM_FAILURE);
}

int	error_enomem(int code, char *msg, void *ptr)
{
	errno = ENOMEM;
	if (msg)
		print_error(PREFIX, msg, STRERROR);
	free(ptr);
	return (code);
}

static int	print_error_2(char *output)
{
	if (ft_pputstr_fd(output, 2) == -1)
	{
		free(output);
		return (SYSTEM_FAILURE);
	}
	free(output);
	return (1);
}

int	print_error(char *prefix, char *command_or_file, char *err_msg)
{
	char	*output;

	output = ft_strdup(prefix);
	if (!(output))
		return (SYSTEM_FAILURE);
	if (command_or_file)
	{
		output = ft_strfjoin(output, command_or_file);
		if (!(output))
			return (SYSTEM_FAILURE);
		output = ft_strfjoin(output, ": ");
		if (!(output))
			return (SYSTEM_FAILURE);
	}
	if (err_msg == STRERROR)
		output = ft_strfjoin(output, strerror(errno));
	else
		output = ft_strfjoin(output, err_msg);
	if (!(output))
		return (SYSTEM_FAILURE);
	output = ft_strfjoin(output, "\n");
	if (!(output))
		return (SYSTEM_FAILURE);
	return (print_error_2(output));
}
