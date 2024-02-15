/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_quotes_utils_2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llapage <llapage@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 13:25:28 by llapage           #+#    #+#             */
/*   Updated: 2023/10/01 10:45:19 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_quotes.h"

void	incr_env_var_len(size_t *env_var_len, t_char_list **char_ptr)
{
	while (*char_ptr && is_valid_char((*char_ptr)->character))
	{
		(*env_var_len)++;
		*char_ptr = (*char_ptr)->next;
	}
}

int	quotes_return_failure(void)
{
	print_error(PREFIX, NULL, STRERROR);
	return (SYSTEM_FAILURE);
}

void	set_wildcard(t_char_list **char_ptr)
{
	(*char_ptr)->is_wildcard = 0;
	if ((*char_ptr)->character == '*')
		(*char_ptr)->is_wildcard = 1;
}
