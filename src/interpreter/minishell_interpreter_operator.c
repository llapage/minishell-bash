/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_interpreter_operator.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:18:05 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/17 15:23:14 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_interpreter.h"

int	interpret_operator_node(t_ast **stacked_nodes,
		t_ast **symbol_nodes, t_ast **command_nodes)
{
	if (*symbol_nodes && ast_is_operator((*symbol_nodes)))
	{
		if (link_nodes(ast_pop(symbol_nodes), ast_pop(command_nodes),
				ast_pop(command_nodes), command_nodes))
		{
			free_stacked_nodes(*stacked_nodes, *symbol_nodes, *command_nodes);
			return (1);
		}
	}
	ast_push(symbol_nodes, stacked_nodes);
	return (0);
}
