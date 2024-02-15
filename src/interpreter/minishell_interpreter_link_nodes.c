/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_interpreter_link_nodes.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:18:49 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/29 12:06:19 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_interpreter.h"

int	link_nodes(t_ast *node, t_ast *right, t_ast *left,
		t_ast **command_nodes)
{
	if (((!(left)) || (!(right)))
		&& (!(ast_is_subshell(node))))
	{
		print_error(SYNTAX_PREFIX, NULL, "'newline'");
		return (1);
	}
	if (__APPLE__)
	{
		node->left = left;
		node->right = right;
	}
	else
	{
		node->left = right;
		node->right = left;
	}
	node->next = *command_nodes;
	*command_nodes = node;
	return (0);
}
