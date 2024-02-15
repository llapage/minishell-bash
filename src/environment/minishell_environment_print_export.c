/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment_print_export.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:00:29 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/30 18:03:00 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_environment.h"

static int	error_print_env_export(char **sorted_env, char *name)
{
	free_strstr(&sorted_env, ft_strstrlen((const char **)sorted_env));
	free(name);
	print_error(PREFIX, "export", STRERROR);
	return (SYSTEM_FAILURE);
}

static int	print_env_export_2(char **sorted_env, int i)
{
	char	*name;

	name = ft_strdupchr(sorted_env[i], '=');
	if (!(name))
		errno = ENOMEM;
	if (!ft_strchr(sorted_env[i], '='))
	{
		if (ft_pputstr_fd("declare -x ", 1) == -1
			|| ft_pputstr_fd(sorted_env[i], 1) == -1
			|| ft_pputstr_fd("\n", 1) == -1)
			error_print_env_export(sorted_env, name);
	}
	else if ((!(name))
		|| ((!((sorted_env[i][0] == '_' && sorted_env[i][1] == '=')))
				&& (ft_pputstr_fd("declare -x ", 1) == -1
					|| ft_pputstr_fd(name, 1) == -1
					|| ft_pputstr_fd("=", 1) == -1
					|| ft_pputstr_fd("\"", 1) == -1
					|| ft_pputstr_fd(ft_strchr(sorted_env[i], '=') + 1, 1)
					|| ft_pputstr_fd("\"", 1) == -1
					|| ft_pputstr_fd("\n", 1) == -1)))
		return (error_print_env_export(sorted_env, name));
	free(name);
	return (0);
}

int	print_env_export(char **env)
{
	int		i;
	char	**sorted_env;

	i = 0;
	sorted_env = ft_strstrdup((const char **)env);
	if (!(sorted_env))
		return (error_enomem(SYSTEM_FAILURE, "export", NULL));
	ft_sort_strstr_tab(&sorted_env,
		ft_strstrlen((const char **)sorted_env), 1);
	while (sorted_env[i])
	{
		if (print_env_export_2(sorted_env, i))
			return (SYSTEM_FAILURE);
		i++;
	}
	free_strstr(&sorted_env, ft_strstrlen((const char **)sorted_env));
	return (0);
}
