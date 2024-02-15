/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_lexer_verify_syntax_2.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-clee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 08:22:57 by mde-clee          #+#    #+#             */
/*   Updated: 2023/09/29 12:07:01 by mde-clee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_lexer.h"

int	verify_syntax_2(char **input, int state,
		t_token *token, int error_mask)
{
	char	*bash_token;

	if (error_mask & VERTICAL_BAR && **input == '|')
	{
		if (*(*input + 1)
			&& *(*input + 1) == '|')
			bash_token = "`||'";
		else
			bash_token = "`|'";
		if (is_redirection(state))
		{
			if (!(token->word))
				return (print_error(SYNTAX_PREFIX,
						NULL, bash_token));
		}
		else
			return (print_error(SYNTAX_PREFIX, NULL, bash_token));
	}
	else
		return (verify_syntax_3(input, state, token, error_mask));
	return (0);
}
