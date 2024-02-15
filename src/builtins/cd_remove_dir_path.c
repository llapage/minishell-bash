/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_remove_dir_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:47:17 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/01 11:56:43 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_builtins.h"

void	cd_remove_dots(char **path)
{
	t_char_list	*lst_path;
	t_char_list	*next_char;
	char		*path_ptr;

	if (!(*path))
		return ;
	lst_path = NULL;
	path_ptr = *path;
	to_absolute_path_5(&path_ptr, &next_char, &lst_path);
	free(*path);
	*path = NULL;
	*path = char_list_to_str(lst_path);
	char_list_clear(&lst_path);
}

void	cd_remove_dir_path(char **path, t_char_list **next_char,
		t_char_list **abs_path)
{
	char_list_remove_last_dir(abs_path);
	*next_char = NULL;
	*path = *path + 2;
}
