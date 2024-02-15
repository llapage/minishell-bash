/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:12:19 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 17:16:28 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_ast.h"

static void	ast_init(t_ast *node)
{
	node->next = NULL;
	node->prev = NULL;
	node->input_fd = 0;
	node->output_fd = 1;
	node->path = NULL;
	node->args = NULL;
	node->argv = NULL;
	node->argc = 0;
	node->env = NULL;
	node->root_node = NULL;
	node->root_dir = NULL;
	node->left = NULL;
	node->right = NULL;
	node->infiles = NULL;
	node->outfiles = NULL;
	node->heredoc_file = 0;
	node->shell_id = 0;
	node->non_blocking = 0;
	node->no_fork = 0;
	node->pipe_end = 0;
	node->shell_id = 0;
	node->nbr_outfiles = 0;
	node->cwd_file = NULL;
	node->env_file = NULL;
	node->pipe_list = NULL;
}

t_ast	*ast_create(enum e_type type)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
	{
		errno = ENOMEM;
		return (NULL);
	}
	node->type = type;
	if (type == NEW_SEQUENCE)
		node->type = COMMAND;
	ast_init(node);
	return (node);
}
