/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_interpreter_end_subshell.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:16:55 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/17 15:35:53 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_interpreter.h"

int	interpret_end_subshell_node_2(t_ast **stacked_nodes,
		t_ast **symbol_nodes, t_ast **command_nodes)
{
	t_ast	*tmp;

	if (link_nodes(ast_pop(symbol_nodes), ast_pop(command_nodes), NULL,
			command_nodes))
	{
		free_stacked_nodes(*stacked_nodes, *symbol_nodes, *command_nodes);
		return (1);
	}
	tmp = *stacked_nodes;
	*stacked_nodes = (*stacked_nodes)->next;
	free(tmp);
	return (0);
}

int	interpret_end_subshell_node(t_ast **stacked_nodes,
		t_ast **symbol_nodes, t_ast **command_nodes)
{
	if (!(*symbol_nodes))
	{
		print_error(SYNTAX_PREFIX, NULL, "')'");
		free_stacked_nodes(*stacked_nodes, *symbol_nodes, *command_nodes);
		return (1);
	}
	if ((!(*stacked_nodes))
		|| (!(ast_is_end_subshell((*stacked_nodes)))))
		return (0);
	if (ast_is_operator((*symbol_nodes)))
	{
		if (link_nodes(ast_pop(symbol_nodes), ast_pop(command_nodes),
				ast_pop(command_nodes), command_nodes))
		{
			free_stacked_nodes(*stacked_nodes, *symbol_nodes, *command_nodes);
			return (1);
		}
		return (0);
	}
	else if (ast_is_subshell((*symbol_nodes)))
		return (interpret_end_subshell_node_2(stacked_nodes, symbol_nodes,
				command_nodes));
	interpret_end_subshell_node(stacked_nodes, symbol_nodes, command_nodes);
	return (0);
}
