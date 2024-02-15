/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_memory_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 17:20:34 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/17 16:59:26 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_memory.h"

void	free_strstr(char ***strstr, size_t len)
{
	if (!(*strstr))
		return ;
	while (len-- != 0)
	{
		free((*strstr)[len]);
		(*strstr)[len] = NULL;
	}
	free(*strstr);
	*strstr = NULL;
}

static int	is_p_shell_cache(char *file)
{
	if ((!(ft_strcmp(file, ".minishell_env_0")))
		|| (!(ft_strcmp(file, ".minishell_cwd_0")))
		|| (!(ft_strcmp(file, ".minishell_history")))
		|| (!(ft_strcmp(file, ".minishell_exit_code"))))
		return (1);
	return (0);
}

int	clear_subshell_cache(char *root_dir)
{
	DIR				*directory;
	struct dirent	*dir_entry;
	char			*cache_dir;
	char			*file;
	char			*file_path;

	cache_dir = ft_strjoin(root_dir, "/.cache/");
	directory = opendir(cache_dir);
	dir_entry = readdir(directory);
	while (dir_entry)
	{
		file = dir_entry->d_name;
		file_path = ft_strjoin(cache_dir, file);
		if (file[1] && file[1] != '.'
			&& ft_strcmp(file, ".gitkeep")
			&& (!(is_p_shell_cache(file))))
			unlink(file_path);
		free(file_path);
		dir_entry = readdir(directory);
	}
	if (closedir(directory) == -1)
		return (-1);
	free(cache_dir);
	return (0);
}

int	clear_cache(char *root_dir)
{
	DIR				*directory;
	struct dirent	*dir_entry;
	char			*cache_dir;
	char			*file;
	char			*file_path;

	cache_dir = ft_strjoin(root_dir, "/.cache/");
	directory = opendir(cache_dir);
	dir_entry = readdir(directory);
	while (dir_entry)
	{
		file = dir_entry->d_name;
		file_path = ft_strjoin(cache_dir, file);
		if (file[1] && file[1] != '.'
			&& ft_strcmp(file, ".gitkeep")
			&& ft_strcmp(file, ".minishell_history"))
			unlink(file_path);
		free(file_path);
		dir_entry = readdir(directory);
	}
	if (closedir(directory) == -1)
		return (-1);
	free(cache_dir);
	return (0);
}

int	free_ret_1(char *str)
{
	free(str);
	return (1);
}
