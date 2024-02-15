/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_environment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 14:31:48 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/17 17:04:13 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_environment.h"

char	*ft_getenv(char *key, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (key[j])
		{
			if (key[j] != env[i][j])
				break ;
			else
				j++;
		}
		if ((!(key[j])) && env[i][j] == '=')
			return (env[i] + j + 1);
		i++;
	}
	return (NULL);
}

int	print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '=') && (ft_pputstr_fd(env[i], 1) == -1
				|| ft_pputstr_fd("\n", 1) == -1))
		{
			print_error(PREFIX, "env", STRERROR);
			return (SYSTEM_FAILURE);
		}
		i++;
	}
	return (0);
}

static int	env_to_fd(int fd, char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_pputstr_fd(env[i], fd) == -1
			|| ft_pputstr_fd("\n", fd) == -1)
		{
			close(fd);
			return (-1);
		}
		i++;
	}
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int	env_to_file(char **env, char *env_file)
{
	int	fd;
	int	i;

	fd = open(env_file, O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
		return (-1);
	i = 0;
	if (ft_pputstr_fd(env[i], fd) == -1)
	{
		close(fd);
		return (-1);
	}
	i++;
	while (env[i])
	{
		if (i++ && (ft_pputstr_fd("\n", fd) == -1
				|| ft_pputstr_fd(env[i], fd) == -1))
		{
			close(fd);
			return (-1);
		}
	}
	if (close(fd) == -1)
		return (-1);
	return (0);
}

int	create_env_file(char **env, char *root)
{
	int		env_fd;
	char	*file_name;

	file_name = ft_strjoin(root, "/.cache/.minishell_env_0");
	if (!(access(file_name, F_OK)))
	{
		env_fd = open(file_name, O_RDWR, 0666);
		free(file_name);
		close(env_fd);
		return (0);
	}
	env_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	free(file_name);
	if (env_to_fd(env_fd, env))
		return (-1);
	return (0);
}
