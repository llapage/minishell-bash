/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ast_print_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 13:30:45 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/17 18:19:33 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_ast.h"

int	ast_print_tree(t_ast *node)
{
	if (!(node))
		return (0);
	if (node->left)
		ast_print_tree(node->left);
	if (node->right)
		ast_print_tree(node->right);
	if (ast_print_node(node))
		return (-1);
	return (0);
}

int	ast_print_node_args(t_ast *node)
{
	t_arg_list	*arg_ptr;
	t_char_list	*char_ptr;

	arg_ptr = node->args;
	while (arg_ptr)
	{
		if (ft_pputstr_fd("arg list:\t", 1) == -1)
			return (-1);
		char_ptr = arg_ptr->arg;
		while (char_ptr)
		{
			if (ft_pputchar_fd(char_ptr->character, 1) == -1)
				return (-1);
			char_ptr = char_ptr->next;
		}
		if (ft_pputstr_fd("\n", 1) == -1)
			return (-1);
		arg_ptr = arg_ptr->next;
	}
	return (0);
}

int	ast_print_node_argv(t_ast *node)
{
	int			i;

	i = 0;
	while (node->argv && node->argv[i])
	{
		if (ft_pputstr_fd("argv[", 1) == -1
			|| ft_putnbr_base_fd(i, 10, 1) == -1
			|| ft_pputstr_fd("]:\t", 1) == -1
			|| ft_pputstr_fd(node->argv[i], 1) == -1
			|| ft_pputstr_fd("\n", 1))
			return (-1);
		i++;
	}
	if (ft_pputstr_fd("path:\t\t", 1) == -1
		|| ft_pputstr_fd(node->path, 1) == -1
		|| ft_pputstr_fd("\n", 1) == -1)
		return (-1);
	if (node->env)
	{
		if (ft_pputstr_fd("env:\t\t#", 1) == -1
			|| ft_putnbr_base_fd((long)*(node->env), 16, 1) == -1
			|| ft_pputstr_fd("\n", 1) == -1)
			return (-1);
	}
	return (0);
}

int	ast_print_node_env(t_ast *node)
{
	int			i;

	i = 0;
	while (node->env && node->env[i] && i < 1)
	{
		if (ft_pputstr_fd("\t\t", 1) == -1
			|| ft_pputstr_fd(node->env[i++], 1) == -1
			|| ft_pputstr_fd("\n\t\tetc...\n", 1) == -1)
			return (-1);
	}
	if (ft_pputstr_fd("left:\t\t", 1) == -1
		|| ft_putnbr_base_fd((long)node->left, 16, 1) == -1
		|| ft_pputstr_fd("\nright:\t\t", 1) == -1
		|| ft_putnbr_base_fd((long)node->right, 16, 1) == -1
		|| ft_pputstr_fd("\n", 1) == -1)
		return (-1);
	return (0);
}

int	ast_print_stacked_nodes(t_ast *head)
{
	t_ast	*node_ptr;

	node_ptr = head;
	while (node_ptr)
	{
		if (ast_print_node(node_ptr))
			return (-1);
		node_ptr = node_ptr->next;
	}
	return (0);
}
