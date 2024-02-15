/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 09:05:19 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/22 06:25:18 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_quotes.h"

static int	expand_env_var_ret(int ret)
{
	if (ret == SYSTEM_FAILURE)
		print_error(PREFIX, NULL, STRERROR);
	return (ret);
}

int	expand_env_var(t_char_list **char_list, t_char_list **char_ptr,
		char *root_dir, char **env)
{
	int				ret;
	t_char_list		*env_var_start;
	size_t			env_var_len;

	ret = resolve_exit_code(char_list, char_ptr, root_dir);
	if (ret == 1)
		return (0);
	else if (ret == SYSTEM_FAILURE)
		return (quotes_return_failure());
	else if (char_ptr)
	{
		if (expand_env_var_2(&env_var_start, &env_var_len, char_list, char_ptr))
			return (0);
		ret = char_list_env_expand(char_list, env_var_start,
				env_var_len, env);
		if (ret)
			return (expand_env_var_ret(ret));
		if (*char_ptr && (*char_ptr)->character == '\"')
			return (0);
	}
	return (0);
}

static void	resolve_all_quotes_2(t_ast *node)
{
	t_arg_list	*arg_ptr;
	int			ret;

	arg_ptr = node->infiles;
	ret = resolve_infiles_outfiles_quotes(node, arg_ptr);
	if (ret == SYSTEM_FAILURE)
		free_and_exit(node->root_node, SYSTEM_FAILURE);
	else if (ret == 1)
		free_and_exit(node->root_node, 1);
}

void	resolve_all_quotes(t_ast *node)
{
	t_arg_list	*arg_ptr;
	t_arg_list	*tmp;
	int			ret;
	int			mode;

	arg_ptr = node->args;
	while (arg_ptr)
	{
		mode = 0;
		if (arg_ptr->arg && (arg_ptr->arg->character == '\"'
				|| arg_ptr->arg->character == '\''))
			arg_ptr->empty = 1;
		ret = resolve_quotes(&arg_ptr, &(arg_ptr->arg), node, &mode);
		if (ret == SYSTEM_FAILURE)
			free_and_exit(node->root_node, SYSTEM_FAILURE);
		tmp = arg_ptr->next;
		if (!(arg_ptr->arg) && arg_ptr->empty != 1)
			arg_list_remove(&(node->args), arg_ptr);
		arg_ptr = tmp;
	}
	resolve_all_quotes_2(node);
}
