/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expander_wildcard.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:04:14 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 16:19:15 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_expander.h"

void	set_arg_list(char **array, t_char_list *pattern, t_arg_list **args,
		int *match)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i][0] != '.'
				&& pattern_match(array[i], pattern, pattern))
		{
			arg_list_add(args, str_to_char_list(array[i]));
			*match = 1;
		}
		i++;
	}
}

int	wildcard_expander(t_ast *node, t_arg_list **args,
		t_char_list *pattern, int *match)
{
	char	*cwd_file;
	char	*root_dir;
	char	*cwd;
	char	**array;

	cwd_file = node->cwd_file;
	root_dir = node->root_dir;
	cwd = get_cwd(cwd_file, root_dir);
	if (!(cwd))
		return (-1);
	array = get_dir_array(cwd);
	free(cwd);
	if (!array)
		exit_malloc_fail(node->root_node);
	set_arg_list(array, pattern, args, match);
	return (0);
}
