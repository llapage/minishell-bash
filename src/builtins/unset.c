/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 17:22:05 by llapage           #+#    #+#             */
/*   Updated: 2023/10/17 16:22:28 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_builtins.h"

static int	unset_var_3(char ***env, char *env_file, int i)
{
	char	**new_env;

	free((*env)[i]);
	(*env)[i] = (*env)[i + 1];
	i++;
	while ((*env)[i])
	{
		(*env)[i] = (*env)[i + 1];
		i++;
	}
	new_env = ft_strstrdup((const char **)*env);
	if (!(new_env))
		return (1);
	free_strstr(env, ft_strstrlen((const char **)*env));
	*env = ft_strstrdup((const char **)new_env);
	free_strstr(&new_env, ft_strstrlen((const char **)new_env));
	if (!(*env))
		return (1);
	if (env_to_file(*env, env_file))
	{
		free_strstr(env, ft_strstrlen((const char **)*env));
		return (1);
	}
	return (0);
}

int	unset_var_2(t_ast *node, int k)
{
	int	i;
	int	j;

	i = 0;
	while (node->env[i])
	{
		j = 0;
		while (node->argv[k][j])
		{
			if (node->argv[k][j] != node->env[i][j])
				break ;
			j++;
		}
		if ((!(node->argv[k][j])) && (node->env[i][j] == '='
			|| !ft_strchr(node->env[i], '=')))
		{
			if (unset_var_3(&node->env, node->env_file, i) == 1)
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}

int	unset_var(t_ast *node)
{
	int	k;
	int	ret;

	if (node->input_fd != STDIN_FILENO)
		return (0);
	k = 1;
	while (node->argv[k])
	{
		if (!(is_valid(node->argv[k])) && print_env_error(0, node->argv[k]))
			return (1);
		ret = unset_var_2(node, k);
		if (ret)
			return (ret);
		k++;
	}
	while (k++ <= node->nbr_args)
		print_error(PREFIX, "unset: `'", "not a valid identifier");
	return (0);
}
