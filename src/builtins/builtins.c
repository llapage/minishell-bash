/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 20:15:14 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 18:53:58 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_builtins.h"

int	print_env_error(int mode, char *input)
{
	char	*tmp;

	if (mode == 0)
		tmp = ft_strjoin("unset: `", input);
	else
		tmp = ft_strjoin("export: `", input);
	if (!tmp)
		return (error_enomem(-1, NULL, NULL));
	tmp = ft_strfjoin(tmp, "'");
	if (!tmp)
		return (error_enomem(-1, NULL, NULL));
	print_error(PREFIX, tmp, "not a valid identifier");
	free(tmp);
	return (1);
}

void	check_builtin(t_ast *node)
{
	char	**argv;
	char	***env;

	argv = node->argv;
	env = &node->env;
	if (argv)
	{
		if (!(ft_strcmp(argv[0], "export")))
			free_and_exit(node->root_node, export_var_builtin(node));
		else if (!(ft_strcmp(argv[0], "cd")))
			free_and_exit(node->root_node, set_cwd(node));
		else if (!(ft_strcmp(argv[0], "env")))
			free_and_exit(node->root_node, print_env(*env));
		else if (!(ft_strcmp(argv[0], "unset")))
			free_and_exit(node->root_node, unset_var(node));
		else if (!(ft_strcmp(argv[0], "echo")))
			free_and_exit(node->root_node, echo(argv));
		else if (!(ft_strcmp(argv[0], "pwd")))
			free_and_exit(node->root_node, pwd(*env));
		else if (!(ft_strcmp(argv[0], "exit")))
			free_and_exit(node->root_node, exit_builtin(node, node->argc,
					argv, node->root_dir));
	}
}
