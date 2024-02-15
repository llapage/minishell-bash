/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quotes_single_double.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:21:32 by llapage           #+#    #+#             */
/*   Updated: 2023/10/22 06:24:40 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_quotes.h"

int	resolve_exit_code(t_char_list **char_list, t_char_list **char_ptr,
	char *root_dir)
{
	if ((*char_ptr)->next && (*char_ptr)->next->character == '?')
	{
		char_list_remove(char_list, char_ptr);
		char_list_remove(char_list, char_ptr);
		if (expand_exit_code(char_list, root_dir))
			return (SYSTEM_FAILURE);
		return (1);
	}
	return (0);
}

int	expand_env_var_2(t_char_list **env_var_start,
size_t *env_var_len, t_char_list **char_list, t_char_list **char_ptr)
{
	*env_var_start = (*char_ptr)->next;
	*env_var_len = 0;
	char_list_remove(char_list, char_ptr);
	if (*char_ptr && ft_isdigit((*char_ptr)->character))
	{
		char_list_remove(char_list, char_ptr);
		return (1);
	}
	while (*char_ptr && (ft_isalnum((*char_ptr)->character)
			|| (*char_ptr)->character == '_'))
	{
		(*env_var_len)++;
		*char_ptr = (*char_ptr)->next;
	}
	return (0);
}

int	resolve_double_quotes_2(char **env, t_char_list **char_list,
	t_char_list **char_ptr)
{
	t_char_list	*env_var_start;
	size_t		env_var_len;
	int			ret;

	if (expand_env_var_2(&env_var_start, &env_var_len, char_list, char_ptr))
		return (0);
	ret = char_list_env_expand(char_list, env_var_start,
			env_var_len, env);
	if (ret)
	{
		if (ret == SYSTEM_FAILURE)
			print_error(PREFIX, NULL, STRERROR);
		return (ret);
	}
	return (0);
}

int	resolve_double_quotes(t_char_list **char_list, t_char_list **char_ptr,
			char **env, char *root_dir)
{
	int			ret;

	char_list_remove(char_list, char_ptr);
	set_wildcard(char_ptr);
	while (*char_ptr && (*char_ptr)->character != '\"')
	{
		if ((*char_ptr)->character == '$')
		{
			ret = resolve_exit_code(char_list, char_ptr, root_dir);
			if (ret == 1)
				continue ;
			if (ret == SYSTEM_FAILURE)
				return (quotes_return_failure());
			ret = resolve_double_quotes_2(env, char_list, char_ptr);
			if (ret == 1)
				continue ;
			else if (ret)
				return (ret);
		}
		else
			*char_ptr = (*char_ptr)->next;
	}
	return (char_list_remove(char_list, char_ptr));
}

void	resolve_single_quotes( t_char_list **char_list,
			t_char_list **char_ptr)
{
	char_list_remove(char_list, char_ptr);
	while (*char_ptr && (*char_ptr)->character != '\'')
	{
		(*char_ptr)->is_wildcard = 0;
		if ((*char_ptr)->character == '*')
			(*char_ptr)->is_wildcard = 1;
		*char_ptr = (*char_ptr)->next;
	}
	char_list_remove(char_list, char_ptr);
}
