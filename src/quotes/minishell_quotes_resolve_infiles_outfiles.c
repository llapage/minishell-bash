/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quotes_resolve_infiles_outfiles.c        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:19:04 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/16 16:17:42 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_quotes.h"

static int	resolve_redirections_arg_2(t_arg_list *arg_ptr, int mode,
		int ret, char *tmp_str)
{
	if (mode == DOUBLE_QUOTES)
	{
		if (ret == 1)
			print_error(PREFIX, tmp_str, "ambiguous redirect");
		if (ret)
			return (1);
	}
	else
	{
		if (ret == 1 || char_list_contains_space(arg_ptr->arg))
			print_error(PREFIX, tmp_str, "ambiguous redirect");
		if (ret || char_list_contains_space(arg_ptr->arg))
			return (1);
	}
	free(tmp_str);
	return (0);
}

static int	resolve_redirections_arg(t_arg_list *arg_ptr, t_ast *node)
{
	char		*tmp_str;
	int			ret;
	int			mode;
	t_arg_list	*tmp;

	while (arg_ptr)
	{
		tmp_str = char_list_to_str(arg_ptr->arg);
		if (!(tmp_str))
		{
			print_error(PREFIX, NULL, STRERROR);
			return (SYSTEM_FAILURE);
		}
		mode = REDIRECTION;
		ret = resolve_quotes(&arg_ptr, &(arg_ptr->arg), node, &mode);
		if (resolve_redirections_arg_2(arg_ptr, mode, ret, tmp_str))
			return (free_ret_1(tmp_str));
		tmp = arg_ptr->next;
		if (!(arg_ptr->arg))
			arg_list_remove(&(node->args), arg_ptr);
		arg_ptr = tmp;
	}
	return (0);
}

int	resolve_infiles_outfiles_quotes(t_ast *node, t_arg_list *arg_ptr)
{
	int	ret;

	ret = resolve_redirections_arg(arg_ptr, node);
	if (ret)
		return (ret);
	arg_ptr = node->outfiles;
	ret = resolve_redirections_arg(arg_ptr, node);
	if (ret)
		return (ret);
	return (0);
}
