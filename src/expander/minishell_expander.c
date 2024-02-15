/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_expander.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 09:45:15 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/22 23:52:24 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_expander.h"

static void	expander_2(t_ast *node, t_arg_list **args, t_arg_list **current_arg)
{
	t_arg_list	*wildcard_ptr;
	int			match;

	if (char_list_chr((*current_arg)->arg, '*'))
	{
		match = 0;
		if (wildcard_expander(node, args, (*current_arg)->arg, &match) == -1)
		{
			free_tree(node->root_node);
			print_error(PREFIX, NULL, STRERROR);
			exit (SYSTEM_FAILURE);
		}
		if (match)
		{
			wildcard_ptr = *current_arg;
			*current_arg = (*current_arg)->next;
			arg_list_remove(args, wildcard_ptr);
			return ;
		}
	}
	*current_arg = (*current_arg)->next;
}

void	expander(t_ast *node, t_arg_list **args, int mode)
{
	t_arg_list	*current_arg;
	char		*str;

	current_arg = *args;
	if (!mode)
	{
		str = char_list_to_str(current_arg->arg);
		if (!str)
			exit_malloc_fail(node->root_node);
		if (!(ft_strcmp("export", str)))
		{
			free(str);
			return ;
		}
		free(str);
	}
	while (current_arg)
		expander_2(node, args, &current_arg);
}
