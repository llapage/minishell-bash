/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expander_wildcard_get_arr.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 13:52:59 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/27 18:15:00 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_expander.h"

char	**get_dir_array_4(DIR *directory, char **dir_array, size_t i)
{
	if (closedir(directory) == -1 || errno)
	{
		free_strstr(&dir_array, i);
		return (NULL);
	}
	ft_sort_strstr_tab(&dir_array, ft_strstrlen((const char **)dir_array), 1);
	return (dir_array);
}

char	**get_dir_array_3(DIR *directory, struct dirent *dir_entry,
		size_t size, char **dir_array)
{
	size_t	i;

	i = 0;
	while (dir_entry && i < size)
	{
		if (errno)
		{
			closedir(directory);
			free_strstr(&dir_array, i);
			return (NULL);
		}
		if (dir_entry->d_name[0] != '.')
		{
			dir_array[i] = ft_strdup(dir_entry->d_name);
			if (!(dir_array[i++]))
			{
				closedir(directory);
				free_strstr(&dir_array, i);
				return (NULL);
			}
		}
		dir_entry = readdir(directory);
	}
	return (get_dir_array_4(directory, dir_array, i));
}

char	**get_dir_array_2(char *cwd, DIR *directory, struct dirent *dir_entry,
		size_t size)
{
	char			**dir_array;

	if (closedir(directory) == -1
		|| errno)
		return (NULL);
	dir_array = malloc((size + 1) * sizeof(char *));
	if (!(dir_array))
		return (NULL);
	dir_array[size] = NULL;
	directory = opendir(cwd);
	if (!(directory))
	{
		free_strstr(&dir_array, 0);
		return (NULL);
	}
	dir_entry = readdir(directory);
	return (get_dir_array_3(directory, dir_entry, size, dir_array));
}

char	**get_dir_array(char *cwd)
{
	DIR				*directory;
	size_t			size;
	struct dirent	*dir_entry;

	directory = opendir(cwd);
	if (!(directory))
		return (NULL);
	errno = 0;
	size = 0;
	dir_entry = readdir(directory);
	while (dir_entry)
	{
		if (errno)
		{
			closedir(directory);
			return (NULL);
		}
		if (dir_entry->d_name[0] != '.')
			size++;
		dir_entry = readdir(directory);
	}
	return (get_dir_array_2(cwd, directory, dir_entry, size));
}
