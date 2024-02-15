/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:37:45 by llapage           #+#    #+#             */
/*   Updated: 2023/10/17 16:18:34 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_builtins.h"

int	export_var(char *name, char *value, char ***env, char *env_file)
{
	char	*line;

	line = create_line(name, value);
	if (!(line))
		return (-1);
	if (!(check_replace(env, line)))
		*env = add_line_env(*env, line);
	if (!(*env))
		return (-1);
	free(line);
	if (env_to_file(*env, env_file))
		return (-1);
	return (0);
}

static int	export_var_builtin_3(t_ast *node, char *line, int *i)
{
	int	ret;

	ret = check_replace(&node->env, line);
	if (ret == SYSTEM_FAILURE)
	{
		free(line);
		print_error(PREFIX, "export", STRERROR);
		return (SYSTEM_FAILURE);
	}
	else if (ret == 0)
		node->env = add_line_env(node->env, line);
	free(line);
	if (!node->env)
		exit_malloc_fail(node->root_node);
	if (env_to_file(node->env, node->env_file))
	{
		print_error(PREFIX, "export", STRERROR);
		return (SYSTEM_FAILURE);
	}
	(*i)++;
	return (0);
}

static int	export_var_builtin_2(t_ast *node, int *i)
{
	char	*line;
	char	*name;
	char	*value;

	if (ft_strchr(node->argv[*i], '='))
		name = ft_strdupchr(node->argv[*i], '=');
	else
		name = ft_strdup(node->argv[*i]);
	if (!(name))
		return (error_enomem(SYSTEM_FAILURE, "export", NULL));
	if (ft_strchr(node->argv[*i], '='))
	{
		value = ft_strchr(node->argv[*i], '=') + 1;
		line = create_line(name, value);
		free(name);
	}
	else
		line = name;
	if (!(line))
	{
		print_error(PREFIX, "export", STRERROR);
		return (SYSTEM_FAILURE);
	}
	return (export_var_builtin_3(node, line, i));
}

int	export_var_builtin(t_ast *node)
{
	int		i;
	int		ret;

	if (!node->nbr_args)
		return (print_env_export(node->env));
	if ((!(node->shell_id)) && node->input_fd != STDIN_FILENO)
		return (0);
	ret = export_error(node->argv);
	if (ret)
		return (ret);
	i = 1;
	while (node->argv[i])
	{
		if (export_var_builtin_2(node, &i))
			return (SYSTEM_FAILURE);
	}
	ret = 0;
	if (i <= node->nbr_args)
		ret = 1;
	if (i == 1)
		return (print_env_export(node->env));
	while (i++ <= node->nbr_args)
		print_error(PREFIX, "export: `'", "not a valid identifier");
	return (ret);
}
