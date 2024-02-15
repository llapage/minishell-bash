/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_to_abs_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 13:51:45 by llapage           #+#    #+#             */
/*   Updated: 2023/10/01 11:53:38 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

int	to_absolute_path_5(char **path, t_char_list **next_char,
		t_char_list **abs_path)
{
	while (**path)
	{
		if (**path == '.' && (!*(*path + 1)))
			(*path)++;
		else if (**path == '.' && (*(*path + 1) == '/'))
			*path = *path + 2;
		else if ((**path == '.' && *(*path + 1) == '.')
			&& ((!(*(*path + 2))) || *(*path + 2) == '/'))
			cd_remove_dir_path(path, next_char, abs_path);
		else
		{
			*next_char = char_list_create(**path);
			if (!(*next_char))
			{
				char_list_clear(abs_path);
				return (1);
			}
			char_list_add(abs_path, *next_char);
			(*path)++;
		}
	}
	return (0);
}

int	to_absolute_path_2(char *path, char **abs_path_str, char **env)
{
	if (!(path))
	{
		*abs_path_str = ft_strdup(ft_getenv("HOME", env));
		if (!(*abs_path_str))
			errno = ENOMEM;
		return (1);
	}
	return (0);
}

int	to_absolute_path_3(t_char_list **abs_path, t_ast *node)
{
	char	*cwd;

	cwd = get_cwd(node->cwd_file, node->root_dir);
	if (!(cwd))
		return (-1);
	*abs_path = str_to_char_list(cwd);
	free(cwd);
	if (!(*abs_path))
		return (-1);
	return (0);
}

int	to_absolute_path_4(char *path, t_char_list *next_char,
		t_char_list **abs_path)
{
	t_char_list	*abs_path_ptr;

	if (*path)
	{
		abs_path_ptr = *abs_path;
		while (abs_path_ptr->next)
			abs_path_ptr = abs_path_ptr->next;
		if (abs_path_ptr->character == '/')
			return (0);
		next_char = char_list_create('/');
		if (!(next_char))
		{
			char_list_clear(abs_path);
			return (-1);
		}
		char_list_add(abs_path, next_char);
	}
	return (0);
}

char	*to_absolute_path(char *input_path, t_ast *node)
{
	t_char_list	*abs_path;
	t_char_list	*next_char;
	char		*path;
	char		*abs_path_str;

	if (input_path && *input_path && *input_path == '.'
		&& (!(*(input_path + 1))))
		return (get_cwd(node->cwd_file, node->root_dir));
	path = input_path;
	next_char = NULL;
	if (to_absolute_path_2(path, &abs_path_str, node->env))
		return (abs_path_str);
	if (to_absolute_path_3(&abs_path, node))
		return (NULL);
	if (to_absolute_path_4(path, next_char, &abs_path))
		return (NULL);
	if (to_absolute_path_5(&path, &next_char, &abs_path))
		return (NULL);
	if (next_char && next_char->character == '/')
		char_list_remove(&abs_path, &next_char);
	abs_path_str = char_list_to_str(abs_path);
	char_list_clear(&abs_path);
	return (abs_path_str);
}
