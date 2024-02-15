/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ast_is.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:15:39 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/28 09:46:09 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_ast.h"

int	ast_is_command(t_ast *node)
{
	if (node->type == E_COMMAND)
		return (1);
	return (0);
}

int	ast_is_operator(t_ast *node)
{
	if (node->type == E_AND
		|| node->type == E_OR
		|| node->type == E_PIPE)
		return (1);
	return (0);
}

int	ast_is_subshell(t_ast *node)
{
	if (node->type == E_SUBSHELL)
		return (1);
	return (0);
}

int	ast_is_end_subshell(t_ast *node)
{
	if (node->type == E_SUBSHELL_END)
		return (1);
	else
		return (0);
}
