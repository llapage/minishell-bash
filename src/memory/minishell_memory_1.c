/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_memory_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:47:05 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/26 16:49:22 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_memory.h"

void	free_tokens(t_token *head)
{
	t_token	*token_ptr;
	t_token	*next_ptr;

	token_ptr = head->next;
	while (token_ptr != head)
	{
		next_ptr = token_ptr->next;
		free(token_ptr);
		token_ptr = NULL;
		token_ptr = next_ptr;
	}
	free(head);
	head = NULL;
}

void	free_node(t_ast *node)
{
	free(node->env_file);
	node->env_file = NULL;
	free(node->cwd_file);
	node->cwd_file = NULL;
	free(node->root_dir);
	node->root_dir = NULL;
	arg_list_clear(&node->args);
	arg_list_clear(&node->infiles);
	arg_list_clear(&node->outfiles);
	if (node->argv)
		free_strstr(&(node->argv),
			ft_strstrlen((const char **)node->argv));
	free(node->path);
	node->path = NULL;
	if (node->env)
		free_strstr(&(node->env),
			ft_strstrlen((const char **)node->env));
	free(node);
	node = NULL;
}

void	free_tree2(t_ast *node)
{
	if (__APPLE__ && node && node->right)
	{
		free_tree2(node->left);
		free_tree2(node->right);
	}
	else if (node && node->left)
	{
		free_tree2(node->left);
		free_tree2(node->right);
	}
	if (node)
		free_node(node);
}

void	free_tree(t_ast *node)
{
	int_list_clear(&node->pipe_list);
	free_tree2(node);
}

void	free_stacked_nodes(t_ast *stacked_nodes, t_ast *symbol_nodes,
		t_ast *command_nodes)
{
	t_ast	*ptr;
	t_ast	*ptr_2;

	ptr = stacked_nodes;
	while (ptr)
	{
		ptr_2 = ptr->next;
		free_node(ptr);
		ptr = ptr_2;
	}
	ptr = symbol_nodes;
	while (ptr)
	{
		ptr_2 = ptr->next;
		free_node(ptr);
		ptr = ptr_2;
	}
	ptr = command_nodes;
	while (ptr)
	{
		ptr_2 = ptr->next;
		free_tree2(ptr);
		ptr = ptr_2;
	}
}
