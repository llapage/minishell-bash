/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_interpreter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 09:33:49 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/28 09:42:28 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_interpreter.h"

int	interpreter_2(t_ast **stacked_nodes, t_ast *command_nodes,
		t_ast *symbol_nodes)
{
	if (symbol_nodes && ast_is_subshell(symbol_nodes))
	{
		print_error(SYNTAX_PREFIX, NULL, "'newline'");
		free_stacked_nodes(*stacked_nodes, symbol_nodes, command_nodes);
		return (1);
	}
	if (symbol_nodes)
	{
		if (link_nodes(ast_pop(&symbol_nodes), ast_pop(&command_nodes),
				ast_pop(&command_nodes), &command_nodes))
		{
			free_stacked_nodes(*stacked_nodes, symbol_nodes, command_nodes);
			return (1);
		}
	}
	*stacked_nodes = command_nodes;
	return (0);
}

int	interpreter(t_ast **stacked_nodes)
{
	t_ast		*command_nodes;
	t_ast		*symbol_nodes;

	command_nodes = NULL;
	symbol_nodes = NULL;
	if (!(*stacked_nodes))
		return (1);
	while (*stacked_nodes)
	{
		if (ast_is_command(*stacked_nodes))
			ast_push(&command_nodes, stacked_nodes);
		else if (ast_is_subshell(*stacked_nodes))
			ast_push(&symbol_nodes, stacked_nodes);
		else if (ast_is_operator(*stacked_nodes))
		{
			if (interpret_operator_node(stacked_nodes, &symbol_nodes,
					&command_nodes))
				return (1);
		}
		else if (ast_is_end_subshell(*stacked_nodes))
			if (interpret_end_subshell_node(stacked_nodes, &symbol_nodes,
					&command_nodes))
				return (1);
	}
	return (interpreter_2(stacked_nodes, command_nodes, symbol_nodes));
}
