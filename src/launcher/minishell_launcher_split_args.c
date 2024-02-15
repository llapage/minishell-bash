/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_launcher_split_args.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 22:55:25 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/17 14:40:26 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_launcher.h"

static void	skip_leading_space(t_char_list **char_ptr, t_arg_list **ptr)
{
	t_char_list	*tmp_char;

	*char_ptr = (*ptr)->arg;
	while (*char_ptr && ft_isspace((*char_ptr)->character))
	{
		tmp_char = *char_ptr;
		*char_ptr = (*char_ptr)->next;
		(*ptr)->arg = *char_ptr;
		free(tmp_char);
		tmp_char = NULL;
	}
}

static void	skip_trailing_space(t_char_list **next_arg, t_char_list **space)
{
	t_char_list	*tmp_char;

	*next_arg = NULL;
	if (*space)
		*next_arg = (*space)->next;
	while (*next_arg && ft_isspace((*next_arg)->character))
	{
		tmp_char = *next_arg;
		*next_arg = (*next_arg)->next;
		free(tmp_char);
		tmp_char = NULL;
	}
	free(*space);
	*space = NULL;
}

static int	split_args_main(t_arg_list **args, t_arg_list *ptr)
{
	t_char_list	*next_arg;
	t_char_list	*char_ptr;
	t_char_list	*space;
	t_arg_list	*tmp;

	if (!(char_list_contains_space(ptr->arg)))
		return (0);
	skip_leading_space(&char_ptr, &ptr);
	while (char_ptr && char_ptr->next
		&& (!(ft_isspace(char_ptr->next->character))))
		char_ptr = char_ptr->next;
	space = char_ptr->next;
	char_ptr->next = NULL;
	skip_trailing_space(&next_arg, &space);
	if (!(next_arg))
		return (0);
	if (arg_list_insert(args, ptr, next_arg))
		return (-1);
	if (ptr->arg == NULL)
	{
		tmp = ptr;
		ptr = ptr->next;
		arg_list_remove(args, tmp);
	}
	return (0);
}

void	split_args(t_ast *node)
{
	t_arg_list	*arg_ptr;

	free_strstr(&node->argv, ft_strstrlen((const char **)node->argv));
	arg_ptr = node->args;
	while (arg_ptr)
	{
		if (arg_ptr->split == 1)
		{
			if (split_args_main(&node->args, arg_ptr))
				launcher_fail(node->root_node, NULL, STRERROR, 1);
		}
		arg_ptr = arg_ptr->next;
	}
	node->argv = arg_list_to_str_arr(node->args);
	if ((!(node->argv)) && errno == ENOMEM)
		launcher_fail(node->root_node, NULL, STRERROR, 1);
	node->argc = arg_list_len(node->args);
}
