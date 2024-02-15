/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_get_cwd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 09:57:29 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/27 11:15:11 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_builtins.h"

static int	get_parent_cwd_2(char **file, char **cwd, char *nb)
{
	*file = ft_strfjoin(*file, "_");
	if (!(*file))
	{
		free(nb);
		return (*cwd = NULL, 1);
	}
	*file = ft_strfjoin(*file, nb);
	free(nb);
	if (!(*file))
		return (*cwd = NULL, 1);
	return (0);
}

static int	get_parent_cwd(char *cwd_file, char **file, char **cwd,
				char *root_dir)
{
	char	*nb;

	nb = ft_strrchr(*file, '_') + 1;
	nb = ft_itoa(ft_atoi(nb) - 1);
	free(*file);
	if (!(nb))
		return (*cwd = NULL, 1);
	if (ft_atoi(nb) == -1)
	{
		free(nb);
		*cwd = ft_strdup(root_dir);
		return (1);
	}
	*file = ft_strduprchr(cwd_file, '_');
	if (!(*file))
	{
		free(nb);
		return (*cwd = NULL, 1);
	}
	return (get_parent_cwd_2(file, cwd, nb));
}

char	*get_cwd(char *cwd_file, char *root_dir)
{
	int		fd;
	char	*cwd;
	char	*file;

	file = ft_strdup(cwd_file);
	if (!(file))
		return (errno = ENOMEM, NULL);
	while (access(file, F_OK) == -1)
		if (get_parent_cwd(cwd_file, &file, &cwd, root_dir))
			return (errno = ENOMEM, cwd);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd < 0)
		return (NULL);
	cwd = get_next_line(fd);
	if (!(cwd))
		errno = ENOMEM;
	if (close(fd) == -1)
	{
		free(cwd);
		return (NULL);
	}
	return (cwd);
}
