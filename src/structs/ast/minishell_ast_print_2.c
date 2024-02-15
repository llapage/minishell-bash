/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_ast_print_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 18:03:32 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 17:15:54 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_ast.h"

static int	ast_print_node_type(t_ast *node)
{
	char	*type;

	type = ditoa(node->type);
	if (!(type))
		return (-1);
	if (ft_pputstr_fd("\n>>NODE<<\n", 1) == -1
		|| ft_putnbr_base_fd((long)node, 16, 1) == -1
		|| ft_pputstr_fd("\ntype:\t\t", 1) == -1
		|| ft_pputstr_fd(type, 1) == -1)
	{
		free(type);
		return (-1);
	}
	free(type);
	return (0);
}

static int	ast_print_node_infiles(t_ast *node)
{
	t_arg_list	*arg_ptr;

	if (ft_pputstr_fd("\ninput_files:\n", 1) == -1)
		return (-1);
	arg_ptr = node->infiles;
	while (arg_ptr)
	{
		if (ft_pputstr_fd("\t\t", 1) == -1
			|| char_list_print(arg_ptr->arg) == -1
			|| ft_pputstr_fd("\n", 1) == -1)
			return (-1);
		arg_ptr = arg_ptr->next;
	}
	return (0);
}

static int	ast_print_node_outfiles(t_ast *node)
{
	t_arg_list	*arg_ptr;

	if (ft_pputstr_fd("\ninput_fd:\t", 1) == -1
		|| ft_putnbr_base_fd(node->input_fd, 10, 1) == -1
		|| ft_pputstr_fd("\nheredoc_file:\t", 1) == -1
		|| ft_putnbr_base_fd(node->heredoc_file, 10, 1) == -1
		|| ft_pputstr_fd("\noutput_files:\n", 1) == -1)
		return (-1);
	arg_ptr = node->outfiles;
	while (arg_ptr)
	{
		if (ft_pputstr_fd("\t\t", 1) == -1
			|| char_list_print(arg_ptr->arg) == -1
			|| ft_pputstr_fd("\n", 1) == -1)
			return (-1);
		arg_ptr = arg_ptr->next;
	}
	return (0);
}

static int	ast_print_node_shell_id(t_ast *node)
{
	if (ft_pputstr_fd("output_fd:\t", 1) == -1
		|| ft_putnbr_base_fd(node->output_fd, 10, 1) == -1
		|| ft_pputstr_fd("\nshell_id:\t", 1) == -1
		|| ft_putnbr_base_fd(node->shell_id, 10, 1) == -1
		|| ft_pputstr_fd("\n", 1) == -1)
		return (-1);
	return (0);
}

int	ast_print_node(t_ast *node)
{
	if (ast_print_node_type(node))
		return (-1);
	if (ast_print_node_infiles(node))
		return (-1);
	if (ast_print_node_outfiles(node))
		return (-1);
	if (ast_print_node_shell_id(node))
		return (-1);
	if (ast_print_node_args(node))
		return (-1);
	if (ast_print_node_argv(node))
		return (-1);
	if (ast_print_node_env(node))
		return (-1);
	if (ft_pputstr_fd("non_blocking:\t", 1) == -1
		|| ft_putnbr_base_fd(node->non_blocking, 10, 1) == -1
		|| ft_pputstr_fd("\npipe_end:\t", 1) == -1
		|| ft_putnbr_base_fd(node->pipe_end, 10, 1) == -1
		|| ft_pputstr_fd("\nno_fork:\t", 1) == -1
		|| ft_putnbr_base_fd(node->no_fork, 10, 1) == -1
		|| ft_pputstr_fd("\n", 1) == -1)
		return (-1);
	return (0);
}
