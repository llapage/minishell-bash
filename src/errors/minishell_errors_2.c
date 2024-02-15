/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_errors_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:35:43 by llapage           #+#    #+#             */
/*   Updated: 2023/10/22 06:37:47 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_errors.h"

void	free_exit_malloc_fail(t_ast *root_node, char *file)
{
	free(file);
	exit_malloc_fail(root_node);
}

void	pipe_fail(t_ast *root_node, char *msg_part_1,
		char *msg_part_2, int exit_code)
{
	print_error(PREFIX, msg_part_1, msg_part_2);
	free_and_exit(root_node, exit_code);
}
