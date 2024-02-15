/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 18:27:49 by llapage           #+#    #+#             */
/*   Updated: 2023/10/02 15:15:54 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_builtins.h"

char	*create_line(char *name, char *value)
{
	char	*line;

	line = ft_strjoin(name, "=");
	if (!(line))
	{
		errno = ENOMEM;
		return (NULL);
	}
	line = ft_strfjoin(line, value);
	if (!(line))
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (line);
}

int	check_replace(char ***env, char *line)
{
	int	i;
	int	size;

	i = 0;
	size = ft_strstrlen((const char **)*env);
	while ((*env)[i])
	{
		if ((!ft_strchr(line, '=') && !strcmp_env((*env)[i], line))
			|| (ft_strchr(line, '=') && !(strcmp_env((*env)[i], line))))
		{
			free((*env)[i]);
			(*env)[i] = ft_strdup(line);
			if (!((*env)[i]))
			{
				free_strstr(env, size);
				return (error_enomem(SYSTEM_FAILURE, NULL, NULL));
			}
			return (1);
		}
		i++;
	}
	return (0);
}

char	**add_line_env(char **env, char *line)
{
	int		i;
	char	**new_env;

	new_env = malloc((ft_strstrlen((const char **)env) + 2)
			* sizeof(char *));
	i = 0;
	if (new_env)
	{
		while (env[i])
		{
			new_env[i] = ft_strdup(env[i]);
			if (!new_env[i])
			{
				while (i-- != 0)
					free(new_env[i]);
				free(new_env);
				return (NULL);
			}
			i++;
		}
		new_env[i] = ft_strjoin(line, "\n");
		new_env[i + 1] = NULL;
	}
	free_strstr(&env, i);
	return (new_env);
}

int	strcmp_env(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	if (s1 && s2)
	{
		str1 = (unsigned char *)s1;
		str2 = (unsigned char *)s2;
		i = 0;
		while (str1[i] && str2[i] && str1[i] == str2[i] && str1[i] != '='
			&& str2[i] != '=')
			i++;
		if ((str1[i] && str2[i] && str1[i] == '=' && str2[i] == '=') || !str1[i]
			|| (!str2[i] && str1[i] != '=') || str1[i] == '\n'
			|| str2[i] == '\n')
			return (0);
		else
			return (1);
	}
	return (0);
}
