/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:50:54 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/02 13:51:53 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_builtins.h"

int	is_valid(char *arg)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static char	*create_tmp(char *argv)
{
	char	*tmp;

	tmp = ft_strjoin("export: ", "'");
	if (!(tmp))
		return (NULL);
	tmp = ft_strfjoin(tmp, argv);
	if (!(tmp))
		return (NULL);
	tmp = ft_strfjoin(tmp, "'");
	if (!(tmp))
		return (NULL);
	return (tmp);
}

int	export_error(char **argv)
{
	int		i;
	char	*tmp;
	int		not_valid;

	i = 0;
	not_valid = 0;
	while (argv[i])
	{
		if (!(is_valid(argv[i])))
		{
			not_valid = 1;
			tmp = create_tmp(argv[i]);
			if (!tmp)
				return (error_enomem(SYSTEM_FAILURE, "export", NULL));
			print_error(PREFIX, tmp, "not a valid identifier");
			free(tmp);
		}
		i++;
	}
	return (not_valid);
}
