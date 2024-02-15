/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_finalizer_set_various.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:31:29 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 17:45:58 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_finalizer.h"

static int	set_various_malloc_fail(t_ast *root_node)
{
	free_tree(root_node);
	errno = ENOMEM;
	return (-1);
}

static int	set_various_command_node_2(t_ast *node, char *tmp,
		char *shell_id_ascii, char *root_dir)
{
	char	*env_path;
	char	*cwd_path;

	env_path = ft_strfjoin(tmp, shell_id_ascii);
	if (!(env_path))
	{
		free(shell_id_ascii);
		return (set_various_malloc_fail(node->root_node));
	}
	node->env_file = env_path;
	tmp = ft_strjoin(root_dir, "/.cache/.minishell_cwd_");
	if (!(tmp))
	{
		free(shell_id_ascii);
		return (set_various_malloc_fail(node->root_node));
	}
	cwd_path = ft_strfjoin(tmp, shell_id_ascii);
	free(shell_id_ascii);
	if (!(cwd_path))
		return (set_various_malloc_fail(node->root_node));
	node->cwd_file = cwd_path;
	return (0);
}

static int	set_various_command_node(t_ast *root_node, t_ast *node,
		int shell_id, char *root_dir)
{
	char	*tmp;
	char	*shell_id_ascii;

	node->root_node = root_node;
	node->shell_id = shell_id;
	node->root_dir = ft_strdup(root_dir);
	if (!(node->root_dir))
	{
		errno = ENOMEM;
		return (-1);
	}
	shell_id_ascii = ft_itoa(shell_id);
	if (!(shell_id_ascii))
		return (set_various_malloc_fail(node->root_node));
	tmp = ft_strjoin(root_dir, "/.cache/.minishell_env_");
	if (!(tmp))
	{
		free(shell_id_ascii);
		return (set_various_malloc_fail(node->root_node));
	}
	return (set_various_command_node_2(node, tmp, shell_id_ascii, root_dir));
}

static int	set_various_not_command_node(t_ast *root_node, t_ast *node,
		int shell_id, char *root_dir)
{
	node->root_node = root_node;
	node->root_dir = ft_strdup(root_dir);
	if (!(node->root_dir))
		return (error_enomem(-1, NULL, NULL));
	set_various(root_node, node->left, shell_id, root_dir);
	set_various(root_node, node->right, shell_id, root_dir);
	return (0);
}

int	set_various(t_ast *root_node, t_ast *node, int shell_id, char *root_dir)
{
	int	ret;

	if (!(node))
		return (0);
	if (node->type == E_SUBSHELL)
		shell_id++;
	if (node->type != E_COMMAND)
	{
		ret = set_various_not_command_node(root_node, node, shell_id, root_dir);
		if (ret == -1)
			return (ret);
	}
	else
	{
		ret = set_various_command_node(root_node, node, shell_id, root_dir);
		if (ret == -1)
			return (ret);
	}
	return (0);
}
