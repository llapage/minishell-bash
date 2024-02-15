/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quotes_resolve_quotes.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:14:36 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/22 04:58:30 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_quotes.h"

static int	resolve_quotes_5(t_arg_list **arg_ptr, t_char_list **char_ptr,
		t_char_list **char_list)
{
	(void)arg_ptr;
	*char_ptr = *char_list;
	if (!(*char_list))
		return (1);
	return (0);
}

static void	resolve_quotes_4(t_char_list **char_ptr)
{
	set_wildcard(char_ptr);
	*char_ptr = (*char_ptr)->next;
}

static int	resolve_quotes_3(t_char_list **char_list, t_ast *node,
		int *mode, t_char_list **char_ptr)
{
	int	ret;

	if (!(*char_ptr)->next)
	{
		*char_ptr = (*char_ptr)->next;
		return (0);
	}
	ret = expand_env_var(char_list, char_ptr, node->root_dir, node->env);
	if (ret == 1 && *mode == REDIRECTION)
		return (1);
	else if (ret == SYSTEM_FAILURE)
		return (SYSTEM_FAILURE);
	return (0);
}

static int	resolve_quotes_2(t_char_list **char_list, t_ast *node, int *mode,
		t_char_list **char_ptr)
{
	int	ret;

	*mode = DOUBLE_QUOTES;
	ret = resolve_double_quotes(char_list, char_ptr, node->env, node->root_dir);
	if (ret)
		return (ret);
	return (0);
}

int	resolve_quotes(t_arg_list	**arg_ptr,
	t_char_list **char_list, t_ast *node, int *mode)
{
	t_char_list	*char_ptr;
	int			ret;

	if (resolve_quotes_5(arg_ptr, &char_ptr, char_list))
		return (0);
	while (char_ptr)
	{
		ret = 0;
		if (char_ptr->character == '\'')
			resolve_single_quotes(char_list, &char_ptr);
		else if (char_ptr->character == '\"')
			ret = resolve_quotes_2(char_list, node, mode, &char_ptr);
		else if (char_ptr->character == '$')
		{
			(*arg_ptr)->split = 1;
			ret = resolve_quotes_3(char_list, node, mode, &char_ptr);
		}
		else
			resolve_quotes_4(&char_ptr);
		if (ret)
			return (ret);
	}
	return (0);
}
