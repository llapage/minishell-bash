/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parser_heredoc_expand.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 16:58:49 by mde-clee          #+#    #+#             */
/*   Updated: 2023/10/17 18:40:08 by llapage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_parser.h"

int	is_valid_char(char c)
{
	if (!ft_isalnum(c) || c == '_')
		return (0);
	return (1);
}

static void	expand_variable(t_char_list **char_ptr, t_char_list **char_list,
		char **env)
{
	t_char_list	*env_var_start;
	size_t		env_var_len;

	env_var_start = (*char_ptr)->next;
	env_var_len = 0;
	char_list_remove(char_list, char_ptr);
	if (ft_isalpha((*char_ptr)->character))
	{
		while (*char_ptr && is_valid_char((*char_ptr)->character))
		{
			env_var_len++;
			*char_ptr = (*char_ptr)->next;
		}
	}
	else if (*char_ptr)
	{
		char_list_remove(char_list, char_ptr);
		env_var_start = (*char_ptr)->next;
	}
	char_list_env_expand(char_list, env_var_start, env_var_len, env);
}

int	heredoc_expand_input(char **input, char **env)
{
	t_char_list	*char_list;
	t_char_list	*char_ptr;

	if (!(**input))
		return (0);
	char_list = str_to_char_list(*input);
	free(*input);
	*input = NULL;
	if (!(char_list))
		return (-1);
	char_ptr = char_list;
	while (char_ptr)
	{
		if (char_ptr->character == '$')
			expand_variable(&char_ptr, &char_list, env);
		else
			char_ptr = char_ptr->next;
	}
	*input = char_list_to_str(char_list);
	char_list_clear(&char_list);
	if (!(input))
		return (-1);
	return (0);
}
