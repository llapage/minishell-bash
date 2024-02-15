/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_token_print.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <mde-clee@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 14:24:43 by mde-clee          #+#    #+#             */
/*   Updated: 2023/08/31 15:17:41 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_token.h"

int	token_print_one(t_token *token)
{
	char	*str_type;

	if (!(token))
		return (0);
	str_type = ditoa(token->type);
	if (!(str_type))
		return (-1);
	if (ft_pputstr_fd(str_type, 1) == -1
		|| char_list_print(token->word) == -1
		|| ft_pputstr_fd("\n", 1) == -1)
	{
		free(str_type);
		return (-1);
	}
	free(str_type);
	return (0);
}

int	token_print(t_token *token_list)
{
	t_token	*token_ptr;

	if (!(token_list))
		return (0);
	if (token_print_one(token_list) == -1)
		return (-1);
	token_ptr = token_list->next;
	while (token_ptr != token_list)
	{
		if (token_print_one(token_ptr) == -1)
			return (-1);
		token_ptr = token_ptr->next;
	}
	return (0);
}
